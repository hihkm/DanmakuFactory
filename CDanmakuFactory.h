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

#ifndef __C_DANMAKU_FACTORY_H__
#define __C_DANMAKU_FACTORY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Define/DanmakuDef.h"
#include "Define/Status.h"
#include "Config/Config.h"
#include "String/DanmakuFactoryString.h"
#include "List/DanmakuFactoryList.h"

#include "TemplateFile/TemplateFile.h"
#include "AssFile/AssFile.h"

/* xml */
extern int readXml(const char *const ipFile, DANMAKU **head, const char *mode, const float timeShift, STATUS *const status);
extern int writeXml(char const *const fileName, DANMAKU *danmakuHead, STATUS *const status);

/* json */
extern int readJson(const char *const ipFile, DANMAKU **head, const char *mode, const float timeShift, STATUS *const status);
extern int writeJson(const char *const fileName, DANMAKU *danmakuHead, STATUS *const status);

#ifdef __cplusplus
}
#endif

#endif
