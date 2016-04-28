
#include "targettrace.h"

int TargetStatus::radius = 100;

TargetStatus::TargetStatus(CvRect const &rect){    
    this->center_x = int((rect.x+rect.width)/2);
    this->center_y = int((rect.y+rect.height)/2);

    this->mark = 0;
}

int TargetStatus::getDistance(int x,int y){
    double tmp = pow(double(x-center_x),2)\
            +pow(double(y-center_y),2);
    double distance = sqrt(tmp);

    return (int)distance;
}

//--------------------------------------------

TargetTrace::TargetTrace(int threshold)
{
    this->threshold = threshold;
}

int TargetTrace::count(){
    //先判断当前位置
    for (int i = 0;i<targets.size();i++){
        if (targets[i].center_x < threshold){
            targets[i].status_now = TargetStatus::up;
        }else{
            targets[i].status_now = TargetStatus::down;
        }
    }

    //清算变化了的人数
    int count = 0;
    for (int i = 0;i<targets.size();i++){
        if (targets[i].status_now != targets[i].status_init){
            if (targets[i].status_init == TargetStatus::up){
                //最开始是在上，说明现在在下
                count--;
            }
            if (targets[i].status_init == TargetStatus::down){
                //与上面相反
                count++;
            }
            targets[i].status_init = targets[i].status_now;
            //变换状态，以免下次重复检测
        }else{
            continue;
        }
    }
    return count;
}

int TargetTrace::refresh(std::vector<CvRect> &rects){

    int rs = rects.size();
    int ts = targets.size();

    if (rs==ts){
        //已经存在的数量与识别出来的数量相等，可以直接一一对应
        for (int i = 0;i<rs;i++){
            targets.at(i).center_x = rects.at(i).x;
            targets.at(i).center_y = rects.at(i).y;
        }
    }else if (rs>ts){
        //本次识别出来的目标多于已经识别出来的，表示有新目标
        std::cout<<"New Target"<<std::endl;
        int begin_target = 0;
        for (int r_c = 0;r_c+ts<rs;r_c++){
            int min_total_dis = INT_MAX;
            int min_total_tmp = 0;
            for (int t_c = 0;t_c<ts;t_c++){
                TargetStatus target = targets.at(t_c);
                int rect_x = rects.at(r_c+t_c).x;
                int rect_y = rects.at(r_c+t_c).y;
                int dis = target.getDistance(rect_x,rect_y);
                min_total_tmp += dis;
            }
            if (min_total_tmp <= min_total_dis){
                min_total_dis = min_total_tmp;
                begin_target = r_c;
            }
        }
        std::vector<TargetStatus> tmp;
        int j = 0;
        for (int i = 0;i<begin_target;i++,j++){
            tmp.push_back(rects.at(i));
        }
        for (int i = 0;i<targets.size();i++){
            tmp.push_back(targets.at(i));
        }
        for (;j<rects.size();j++){
            tmp.push_back(rects.at(j));
        }
        targets.clear();
        targets.assign(tmp.begin(),tmp.end());
    }else if (rs<ts){
        //与上面的相反
        std::cout<<"Clear Target"<<std::endl;
        int begin_target = 0;
        for (int t_c = 0;t_c+rs<ts;t_c++){
            //类似于动态规划，循环已存的列表
            int min_total_dis = INT_MAX;
            int min_total_tmp = 0;
            for (int r_c = 0;r_c<rs;r_c++){
                TargetStatus target = targets.at(r_c);
                int rect_x = rects.at(r_c+t_c).x;
                int rect_y = rects.at(r_c+t_c).y;
                int dis = target.getDistance(rect_x,rect_y);
                min_total_tmp += dis;
            }
            if (min_total_tmp < min_total_dis){
                min_total_dis = min_total_tmp;
                begin_target = t_c;
            }
        }
        int conserve_begin = begin_target;
        int conserve_end = begin_target + rs;
        std::vector<TargetStatus> tmp;
        for (int i = conserve_begin;i<conserve_end;i++){
            tmp.push_back(targets.at(i));
        }
        targets.clear();
        targets.assign(tmp.begin(),tmp.end());
    }else{
        //理论上不会有这种情况发生，强迫症写上
        //continue;
    }

    //遍历，看人数是否发生变化
    return count();
}
