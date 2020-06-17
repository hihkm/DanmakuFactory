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

#include "Config.h"

/*
 * 从文件读配置文件
 * 参数:配置文件名/默认配置
 * 返回值:配置结构体
 */
CONFIG readConfig(const char *const configFileName, const CONFIG defaultConfig)
{
    int cnt;
    char ch;
    char buf[SIZE_OF_BUF], *bufPtr, *bufCopyPtr;
    CONFIG configOnfile = defaultConfig;
    
    FILE *fptr = fopen(configFileName, "r");
    if (fptr == NULL)
    {
        return configOnfile;
    }
    
    /*找到可读区域*/
    while (fgetc(fptr) != '{' && !feof(fptr)){}
    
    /*读取*/
    cnt = 0;
    while ((ch = fgetc(fptr)) != '}' && !feof(fptr) && cnt < SIZE_OF_BUF - 1)
    {
        buf[cnt] = ch;
        cnt++;
    }
    buf[cnt] = '\0';
    fclose(fptr);
    
    /*解析*/
    bufPtr = buf;
    char key[KEY_LEN];
    char value[VALUE_LEN], *valuePtr;
    char typeName[TYPENAME_LEN];
    while (*bufPtr != '\0')
    {
        /*解析key*/
        if (*bufPtr == ',')
        {/*跳过逗号*/
            bufPtr++;
        }
        strGetLeftPart(key, &bufPtr, ':', KEY_LEN);
        deQuotMarks(key);
        toLower(NULL, key);
        
        /*解析value*/
        valuePtr = value;
        bufCopyPtr = bufPtr;
        if (strchr(bufPtr, ':') != NULL)
        {
            bufPtr = strchr(bufPtr, ':');
            while (bufPtr != bufCopyPtr && *bufPtr != ',')
            {/*向前寻找逗号*/
                bufPtr--;
            }
        }
        else
        {
            if (strrchr(bufPtr, ',') != NULL)
            {
                *(strrchr(bufPtr, ',')) = '\0';
            }
            while (*bufPtr != '\0')
            {
                bufPtr++;
            }
        }
        while (bufCopyPtr != bufPtr)
        {/*拷贝内容*/
            *valuePtr = *bufCopyPtr;
            valuePtr++;
            bufCopyPtr++;
        }
        *valuePtr = '\0';
        deQuotMarks(value);

        /*匹配*/
        valuePtr = value;
        if (strcmp("blockmode", key) == 0)
        {
            int blockmode = 0;
            strGetLeftPart(NULL, &valuePtr, '[', VALUE_LEN);
            while (*valuePtr != '\0')
            {
                /*拆分中括号内用逗号分割的多个值*/ 
                if (strchr(valuePtr, ',') != NULL)
                {/*后半段有逗号*/ 
                    strGetLeftPart(typeName, &valuePtr, ',', TYPENAME_LEN);
                }
                else
                {/*后半段无逗号*/ 
                    strGetLeftPart(typeName, &valuePtr, ']', TYPENAME_LEN);
                    valuePtr += strlen(typeName);/*将指针移到字串末尾以下一个循环跳出*/ 
                }
                
                deQuotMarks(typeName);
                toLower(NULL, typeName);
                
                if (strcmp("r2l", typeName) == 0)
                {
                    blockmode += BLK_R2L;
                }
                else if (strcmp("l2r", typeName) == 0)
                {
                    blockmode += BLK_L2R;
                }
                else if (strcmp("top", typeName) == 0)
                {
                    blockmode += BLK_TOP;
                }
                else if (strcmp("bottom", typeName) == 0)
                {
                    blockmode += BLK_BOTTOM;
                }
                else if (strcmp("special", typeName) == 0)
                {
                    blockmode += BLK_SPECIAL;
                }
                else if (strcmp("color", typeName) == 0 || strcmp("colour", typeName) == 0)
                {/*兼容英式拼写的color*/ 
                    blockmode += BLK_COLOR;
                }
                else if (strcmp("repeat", typeName) == 0)
                {
                    blockmode += BLK_REPEAT; 
                }
            }
            configOnfile.blockmode = blockmode;
        }
        else if (strcmp("statmode", key) == 0)
        {
            /*解析value*/
            int statmode = 0;
            strGetLeftPart(NULL, &valuePtr, '[', VALUE_LEN);
            while (*valuePtr != '\0')
            {
                /*解析中括号内用逗号分割的多个值*/ 
                if (strchr(valuePtr, ',') != NULL)
                {/*后半段有逗号*/ 
                    strGetLeftPart(typeName, &valuePtr, ',', TYPENAME_LEN);
                }
                else
                {/*后半段无逗号*/ 
                    strGetLeftPart(typeName, &valuePtr, ']', TYPENAME_LEN);
                    valuePtr += strlen(typeName);/*将指针移到字串末尾以下一个循环跳出*/ 
                }
                deQuotMarks(typeName);
                toLower(NULL, typeName);
                
                if (strcmp("table", typeName) == 0)
                {
                    statmode += TABLE;
                }
                else if (strcmp("histogram", typeName) == 0)
                {
                    statmode += HISTOGRAM;
                }
            }
            configOnfile.statmode = statmode;
        }
        else if (strcmp("resx", key) == 0)
        {
            configOnfile.resx = atoi(value);
        }
        else if (strcmp("resy", key) == 0)
        {
            configOnfile.resy = atoi(value);
        }
        else if (strcmp("scrolltime", key) == 0)
        {
            configOnfile.scrolltime = atof(value);
        }
        else if (strcmp("fixtime", key) == 0)
        {
            configOnfile.fixtime = atof(value);
        }
        else if (strcmp("density", key) == 0)
        {
            configOnfile.density = atoi(value);
        }
        else if (strcmp("fontname", key) == 0)
        {
            strSafeCopy(configOnfile.fontname, value, FONTNAME_LEN);
        }
        else if (strcmp("fontsize", key) == 0)
        {
            configOnfile.fontsize = atoi(value);
        }
        else if (strcmp("opacity", key) == 0)
        {
            configOnfile.opacity = atoi(value);
        }
        else if (strcmp("outline", key) == 0)
        {
            configOnfile.outline = atoi(value);
        }
        else if (strcmp("shadow", key) == 0)
        {
            configOnfile.shadow = atoi(value);
        }
        else if (strcmp("displayarea", key) == 0)
        {
            configOnfile.displayarea = atof(value);
        }
        else if (strcmp("scrollarea", key) == 0)
        {
            configOnfile.scrollarea = atof(value);
        }
        else if (strcmp("saveblocked", key) == 0)
        {
            toLower(NULL, value);
            if (strcmp("false", value) == 0)
            {
                configOnfile.saveBlockedPart = FALSE;
            }
            else
            {
                configOnfile.saveBlockedPart = TRUE;
            }
        }
    }
    
    return configOnfile;
}


/*
 * 写配置文件
 * 参数：配置文件名/配置信息
 * 返回值：布尔值 是否成功
 */
BOOL writeConfig(const char *const configFileName, const CONFIG newConfig)
{
    FILE *fptr = fopen(configFileName, "w");
    
    CONFIG newConfigCopy = newConfig;
    if (fptr == NULL)
    {
        return FALSE;
    }
    
    fprintf(fptr,
            "{\n"
            "    \"resx\": %d,\n"
            "    \"resy\": %d,\n"
            "    \"scrolltime\": %f,\n"
            "    \"fixtime\": %f,\n"
            "    \"density\": %d,\n"
            "    \"fontname\": \"%s\",\n"
            "    \"fontsize\": %d,\n"
            "    \"opacity\": %d,\n"
            "    \"outline\": %d,\n"
            "    \"shadow\": %d,\n"
            "    \"displayarea\": %f,\n"
            "    \"scrollarea\": %f,\n",
            newConfigCopy.resx,
            newConfigCopy.resy,
            newConfigCopy.scrolltime,
            newConfigCopy.fixtime,
            newConfigCopy.density,
            newConfigCopy.fontname,
            newConfigCopy.fontsize,
            newConfigCopy.opacity,
            newConfigCopy.outline,
            newConfigCopy.shadow,
            newConfigCopy.displayarea,
            newConfigCopy.scrollarea
           );
    
    /*写是否保存屏蔽部分*/
    if (newConfigCopy.saveBlockedPart == FALSE)
    {
        fprintf(fptr, "    \"saveblocked\": false, \n");
    }

    /*写屏蔽模式*/
    {
        /*L2R, R2L, TOP, BOTTOM, SPECIAL, COLOR, REPEAT*/
        fprintf(fptr, "    \"blockmode\": [");
        if (newConfigCopy.blockmode & BLK_L2R)
        {
            fprintf(fptr, "L2R");
            /*判断是否需要逗号*/
            newConfigCopy.blockmode -= BLK_L2R;
            if (newConfigCopy.blockmode != 0)
            {
                fprintf(fptr, ", ");
            }
            
        }
        if (newConfigCopy.blockmode & BLK_R2L)
        {
            fprintf(fptr, "R2L");
            /*判断是否需要逗号*/
            newConfigCopy.blockmode -= BLK_R2L;
            if (newConfigCopy.blockmode != 0)
            {
                fprintf(fptr, ", ");
            }
        }
        if (newConfigCopy.blockmode & BLK_TOP)
        {
            fprintf(fptr, "top");
            /*判断是否需要逗号*/
            newConfigCopy.blockmode -= BLK_TOP;
            if (newConfigCopy.blockmode != 0)
            {
                fprintf(fptr, ", ");
            }
        }
        if (newConfigCopy.blockmode & BLK_BOTTOM)
        {
            fprintf(fptr, "bottom");
            /*判断是否需要逗号*/
            newConfigCopy.blockmode -= BLK_BOTTOM;
            if (newConfigCopy.blockmode != 0)
            {
                fprintf(fptr, ", ");
            }
        }
        if (newConfigCopy.blockmode & BLK_SPECIAL)
        {
            fprintf(fptr, "special");
            /*判断是否需要逗号*/
            newConfigCopy.blockmode -= BLK_SPECIAL;
            if (newConfigCopy.blockmode != 0)
            {
                fprintf(fptr, ", ");
            }
        }
        if (newConfigCopy.blockmode & BLK_COLOR)
        {
            fprintf(fptr, "color");
            /*判断是否需要逗号*/
            newConfigCopy.blockmode -= BLK_COLOR;
            if (newConfigCopy.blockmode != 0)
            {
                fprintf(fptr, ", ");
            }
        }
        if (newConfigCopy.blockmode & BLK_REPEAT)
        {
            fprintf(fptr, "repeat");
            /*判断是否需要逗号*/
            newConfigCopy.blockmode -= BLK_REPEAT;
            if (newConfigCopy.blockmode != 0)
            {
                fprintf(fptr, ", ");
            }
        }
        
        fprintf(fptr, "],\n");
    }
    
    /*写统计模式*/
    {
        /*TABLE, HISTOGRAM*/ 
        fprintf(fptr, "    \"statmode\": [");
        if (newConfigCopy.statmode & TABLE)
        {
            fprintf(fptr, "table");
            /*判断是否需要逗号*/
            newConfigCopy.statmode -= TABLE;
            if (newConfigCopy.statmode != 0)
            {
                fprintf(fptr, ", ");
            }
            
        }
        if (newConfigCopy.statmode & HISTOGRAM)
        {
            fprintf(fptr, "histogram");
            /*判断是否需要逗号*/
            newConfigCopy.statmode -= HISTOGRAM;
            if (newConfigCopy.statmode != 0)
            {
                fprintf(fptr, ", ");
            }
        }
        
        fprintf(fptr, "]\n");
    }
    
    fprintf(fptr, "}");
    
    if (ferror(fptr))
    {
        fclose(fptr);
        return FALSE; 
    }
    
    fclose(fptr);
    
    return TRUE;
}
