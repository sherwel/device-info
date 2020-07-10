//
// Created by 陈颂颂 on 2019/12/27.
//

#include <stdio.h>
#include "include/utils.h"
#include "include/log.h"

/**
 * 判断文件是否存在
 * path: 路径
 * 返回值 1:文件存在; 0:文件不存在
 */
int exists(const char *path) {
    return access(path, F_OK) == 0 ? 1 : 0;
}

/**
 * 读取系统属性值
 * @param name
 * @return 返回属性长度，若为 0 则不存在当前属性
 */
int getProperty(const char *name, char *dest) {
    return __system_property_get(name, dest);
}

int shellExecute(const char *cmdStr, char *dest, int len) {

    if (cmdStr == NULL || strlen(cmdStr) == 0) {
        return 0;
    }
    LOGE("shellExecute cmd: %s", cmdStr);
    char buf[BUF_SIZE_512];
    FILE *pf = NULL;
    if ((pf = popen(cmdStr, "r+")) == NULL) {
        return 0;
    }
    int n = 0;
    while (fgets(buf, BUF_SIZE_512, pf)) {
        // 读取buf长度
        int buf_len = strlen(buf);
        n += buf_len;
        if (n < len) {
            strncpy(dest + n - buf_len, buf, buf_len);
            if (dest[buf_len - 1] == '\n') {
                dest[buf_len - 1] = '\0';
            } else {
                dest[buf_len] = '\0';
            }
            LOGE("shellExecute: len->%d  content->%s", n, dest);
        } else {
            break;
        }
    }
    pclose(pf);
    if (n == 0) {
        return 0;
    }
    return 1;

}
