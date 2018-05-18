#include "ros/ros.h"
#include "con_esc/MsgControl.h"
//#include <curses.h>
#include <cstdio>
#include <termio.h> //for getch
#define KEYDIR 27
#define KEYMIDDLE 91
#define LEFT 68
#define RIGHT 67
#define UP 65
#define DOWN 66

using namespace std;

int getch(void){
    int ch;
    struct termios buf, save;
    tcgetattr(0,&save);
    buf = save;
    buf.c_lflag &= ~(ICANON|ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &save);
    printf("%d\n",ch);
    return ch;
}

int main(int argc,char **argv)
{
    ros::init(argc,argv,"talker");
    ros::NodeHandle nh;
    ros::Publisher talker = nh.advertise<con_esc::MsgControl>("ros_msg",100);
    con_esc::MsgControl msg;
    ros::Rate loop_rate(10);
    int c;
    while(true)
    {
        printf("into while\n");
        
        //while((c = getch())!=224){
          c = getch();
          if(c == KEYDIR)
          {
			    printf("correct special key\n");
              c = getch();
              if(c != KEYMIDDLE)
                  continue;
              c = getch();
              switch(c)
              {
                  case LEFT:
                      msg.data = LEFT;
                      talker.publish(msg);
                      ROS_INFO("send msg= %d", msg.data);
                      break;
                  case RIGHT:
                      msg.data = RIGHT;
                      talker.publish(msg);
                      ROS_INFO("send msg= %d", msg.data);
                      break;
                  case UP:
                      msg.data = UP;
                      talker.publish(msg);
                      ROS_INFO("send msg= %d", msg.data);
                      break;
                  case DOWN:
                      msg.data = DOWN;
                      talker.publish(msg);
                      ROS_INFO("send msg= %d", msg.data);
                      break;
                  default:
                      break;
              }
          }
       //}
    }
    return 0;
}
