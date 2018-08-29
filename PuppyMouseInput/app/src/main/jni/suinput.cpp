//
// Created by pengtiegang on 18-8-20.
//

#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


#include "suinput.h"

int mouse_fd = -1;
bool absolute = false;

char* UINPUT_FILEPATHS[] = {
        "/dev/uinput",
        //"/android/dev/uinput",
        //"dev/input/uinput",
        //"dev/misc/uinput",
};
#define UINPUT_FILEPATHS_COUNT (sizeof(UINPUT_FILEPATHS) / sizeof(char*))

static int suinput_write(int uinput_fd,uint16_t type, uint16_t code, int32_t value){
    struct input_event event;
    memset(&event, 0, sizeof(event));
    gettimeofday(&event.time, 0);
    event.type = type;
    event.code = code;
    event.value = value;
    if(write(uinput_fd, &event, sizeof(event)) != sizeof(event)){
        return -1;
    }

    return 0;
}

static int suinput_write_syn(int uinput_fd, uint16_t type, uint16_t code, int32_t value){
    if(suinput_write(uinput_fd, type, code, value)){
        return -1;
    }
    return suinput_write(uinput_fd, EV_SYN, SYN_REPORT, 0);
}

int suinput_open(const char* device_name, const struct input_id* id){
    int original_errno = 0;
    int uinput_fd = -1;
    struct uinput_user_dev user_dev;
    int i;

    for(i = 0; i < UINPUT_FILEPATHS_COUNT; ++i){
        uinput_fd = open(UINPUT_FILEPATHS[i], O_WRONLY | O_NONBLOCK);
        if(uinput_fd != -1){
            break;
        }
    }

    if(uinput_fd == -1){
        return -1;
    }

    if(ioctl(uinput_fd,UI_SET_EVBIT,EV_KEY) == -1)
        goto err;

    if(absolute){
        if(ioctl(uinput_fd,UI_SET_EVBIT,EV_ABS) == -1)
            goto err;
    }else{
        if(ioctl(uinput_fd,UI_SET_EVBIT,EV_REL) == -1)
            goto err;
    }

    if(ioctl(uinput_fd,UI_SET_EVBIT,EV_SYN) == -1)
        goto err;
    if(absolute){
        if(ioctl(uinput_fd,UI_SET_ABSBIT,ABS_X) == -1)
            goto err;
        if(ioctl(uinput_fd,UI_SET_ABSBIT,ABS_Y) == -1)
            goto err;
    }else{
        if(ioctl(uinput_fd,UI_SET_RELBIT,REL_X) == -1)
            goto err;
        if(ioctl(uinput_fd,UI_SET_RELBIT,REL_Y) == -1)
            goto err;
    }

    if(ioctl(uinput_fd,UI_SET_KEYBIT,BTN_LEFT) == -1)
        goto err;
    if(ioctl(uinput_fd,UI_SET_KEYBIT,BTN_RIGHT) == -1)
        goto err;

    memset(&user_dev,0, sizeof(user_dev));
    strncpy(user_dev.name,device_name,UINPUT_MAX_NAME_SIZE);
    user_dev.id.bustype = id->bustype;
    user_dev.id.vendor = id->vendor;
    user_dev.id.product = id->product;
    user_dev.id.version = id->version;

    if(absolute){
        user_dev.absmax[ABS_X] = 1280 -1;
        user_dev.absmax[ABS_Y] = 720 -1;
    }


    if(write(uinput_fd,&user_dev, sizeof(user_dev)) != sizeof(user_dev))
        goto err;

    if(ioctl(uinput_fd,UI_DEV_CREATE) == -1){
        goto err;
    }

    sleep(2);

    mouse_fd = uinput_fd;

    return uinput_fd;

err:
    original_errno = errno;

    close(uinput_fd);

    errno = original_errno;
    return -1;
}

int suinput_close(int uinput_fd){
    sleep(2);

    if(ioctl(uinput_fd, UI_DEV_DESTROY) == -1){
        close(uinput_fd);
        return -1;
    }

    if(close(uinput_fd) == -1){
        return -1;
    }
    mouse_fd = -1;
    return 0;
}

int suinput_move_pointer(int uinput_fd, int32_t x, int32_t y){
    if(suinput_write(uinput_fd, EV_REL, REL_X, x)){
        return -1;
    }

    return suinput_write_syn(uinput_fd, EV_REL, REL_Y, y);
}

int suinput_hanle_key(int uinput_fd, uint16_t key_code, u_int32_t key_status){
    return suinput_write_syn(uinput_fd, EV_KEY, key_code, key_status);
}

int handle_mouse_event(const mouse_event* mouseEvent){
    if(mouse_fd == -1){
        return -1;
    }

    switch (mouseEvent->type){
        case EV_REL:
            return suinput_move_pointer(mouse_fd, mouseEvent->x, mouseEvent->y);
        case EV_KEY:
            return suinput_hanle_key(mouse_fd,mouseEvent->key_code, mouseEvent->key_status);
    }
}

int suinput_set_pointer(int32_t x, int32_t y){
    if(mouse_fd == -1){
        return -1;
    }
    if(suinput_write(mouse_fd, EV_ABS, ABS_X, x)){
        return -1;
    }
    return suinput_write_syn(mouse_fd, EV_ABS, ABS_Y, y);
}

