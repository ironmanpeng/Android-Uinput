//
// Created by pengtiegang on 18-8-20.
//

#ifndef PUPPYUINPUT_SUINPUT_H
#define PUPPYUINPUT_SUINPUT_H

#include <stdint.h>
#include <stdbool.h>

#include "include/uinput.h"

struct mouse_event{
    //struct timeval time;
    __u16 type;         //1.EV_KEY鼠标按键事件 2.EV_REL鼠标移动事件
    __s32 x;            //x 鼠标x轴方向移动的距离
    __s32 y;            //y 鼠标y轴方向移动的距离
    __u16 key_code;     //1.BTN_LEFT 鼠标左键 2.BTN_RIGHT 鼠标右键
    __s32 key_status;   //1.KEY_DOWN 鼠标按下 2.KEY_UP 鼠标抬起
};

int suinput_open(const char* device_name, const struct input_id* id);

int suinput_close(int uinput_fd);

int handle_mouse_event(const mouse_event* mouseEvent);

int suinput_set_pointer(int32_t x, int32_t y);

#endif //PUPPYUINPUT_SUINPUT_H
