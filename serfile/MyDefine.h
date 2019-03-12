#ifndef _MYDEFINE_H
#define _MYDEFINE_H

#define TYPE    "type"

/*登录界面 登录，注册时发送 name pw*/
#define SELECT  1
#define INSERT  2
#define NAME	"name"
#define PW      "pw"

/*信息采集发送只有 name*/
#define SELECTER 3

/*主机界面 发送 name id year month day limit*/
#define INSERT_HOST 4
#define DELETE_HOST 5
#define SELECT_HOST 6
#define UPDATE_HOST 7
#define LIMIT		"limit"

#define UPID	"upid"
#define ID		"id"
#define YEAR	"year"
#define MONTH	"month"
#define DAY		"day"
#define TIME	"time"
/* 黑名单时间 */

#define FD      "fd"
#define HOSTFD  -1
#define REASON  "reason"
#define YES     "yes"
#define NO		"no"

#endif
