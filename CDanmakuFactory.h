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
#include "Define/FileDef.h"
#include "Define/Status.h"
#include "Config/Config.h"
#include "String/DanmakuFactoryString.h"
#include "List/DanmakuFactoryList.h"

/* xml */
extern int readXml(const char *const ipFile, DANMAKU **head, const char *mode, const float timeShift, STATUS *const status);
extern int writeXml(char const *const fileName, DANMAKU *danmakuHead, STATUS *const status);

/* json */
extern int readJson(const char *const ipFile, DANMAKU **head, const char *mode, const float timeShift, STATUS *const status);
extern int writeJson(const char *const fileName, DANMAKU *danmakuHead, STATUS *const status); 

/* ass */
extern int readAss(const char *const fileName, DANMAKU **danmakuHead, const char *mode, ASSFILE *assSub, const float timeShift,
                   STATUS *const status
                  );
extern int writeAss(const char *const fileName, DANMAKU *danmakuHead,
                    const CONFIG config, const ASSFILE *const subPart, STATUS *const status
                   );

/* 不常用的ass操作函数 */
extern int readAssFile(ASSFILE *assFile, const char *const fileName);
extern int assFileToDanmaku(ASSFILE *inputSub, DANMAKU **danmakuHead, const char *mode, ASSFILE *outputSub, const float timeShift,
                            STATUS *const status
                           );
extern void writeAssStylesPart(FILE *opF, const int numOfStyles, STYLE *const styles);
extern int writeAssDanmakuPart(FILE *opF,
                               DANMAKU *head, const int resX, const int resY, const int fontSize, const char *fontName,
                               const float rollTime, const float holdTime, const float displayArea, const float rollArea,
                               const int density, const int blockMode, const BOOL saveBlockedPart,
                               STATUS *const status
                              );
extern int writeAssStatPart(FILE *opF, DANMAKU *head, int mode, const int rollTime, const int holdTime,
                            const int density, const int blockMode);

extern void freeAssFile(ASSFILE *assFile);

#ifdef __cplusplus
}
#endif

#endif
