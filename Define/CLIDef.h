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

#ifndef __CLIDEF_H__
#define __CLIDEF_H__


#define GUI_SUPPORT       //给GUI版本提供一些特殊的功能支持

#define VERSION "1.50"
#define EDITION "CLI Beta"
#define CONFIG_FILE_NAME "DanmakuFactoryConfig.json"
#define FILENAME_LEN 1024
#define FORMAT_LEN 16

#define ISFORMAT(str) (!strcmp("ass", str) || !strcmp("xml", str) || !strcmp("json", str))
#define ISNUMBERIC(str) (isDesignatedStr(str, "\"\'-.0123456789"))

struct fileInfo
{
    char fileName[FILENAME_LEN];
    char template[FILENAME_LEN];
    float timeShift;
    BOOL isSet;
};

typedef struct fileInfo FINFO;

#endif
