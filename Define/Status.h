/*
Copyright 2019-2020 hkm(github:hihkm)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef __STATUS_H__
#define __STATUS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DanmakuDef.h"

struct SingleTaskStatus
{
    void *function;
    int totalNum;
    int completedNum;
    
    BOOL isDone;
};

typedef struct SingleTaskStatus STATUS;

#ifdef __cplusplus
}
#endif

#endif
