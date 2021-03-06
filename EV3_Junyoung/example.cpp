#include "h_crane.h"

class Crain : public CraneCrane
{
private:
    ev3dev::touch_sensor touch_q;
    ev3dev::motor a;
    ev3dev::motor b; 
    ev3dev::motor c;
    ev3dev::color_sensor colorSensor;
    ev3dev::ultrasonic_sensor ultra_q;
    
public:
    // Hardware Configuration. 초기화 객체에 알맞은 포트 넣어줌. 
    Crain():m_speed(0), touch_q(ev3dev::INPUT_1),a(ev3dev::OUTPUT_A), b(ev3dev::OUTPUT_B), c(ev3dev::OUTPUT_C), ultra_q(ev3dev::INPUT_4)
    
    {
        
    }
    
    
    
    int m_speed, pose, flag;
    
    double get_distance()
    {
        double dis;
        
        return ultra_q.distance_centimeters();
        
    }
    
    bool is_black()
    {
        return colorSensor.color() == 1;  //검정색이면 1==1 만족, 트루 반환?
    }
    
    bool get_touch_pressed()
    {
        return touch_q.is_pressed();
    }
    
    virtual bool get_down()
    {
        return m_down; //처음엔 다 false로 되어있음. 
    }

    virtual bool get_up()
    {
        return m_up;
    }

    virtual bool get_right()
    {
        return m_right;
    }

    virtual bool get_left()
    {
        return m_left;
    }

    virtual bool get_enter()
    {
        return m_enter;
    }

    virtual bool get_escape()
    {
        return m_escape;
    }
    
    virtual int get_speed()
    {
        return 800;
    }
    
    virtual int get_speed_neck()
    {
        return 600;
    }
    // virtual int  get_speed_foot()
    // {
    //     return 600;
    // }
    
    // virtual int  get_speed_neck()
    // {
    //     return 300;
    // }
    
    virtual int get_speed_hand()
    {
        return 300;
    }

    virtual void set_down(bool val)
    {
        m_down = val;
    }
    
    virtual void set_up(bool val)
    {
        m_up = val;    
    }
    
    virtual void set_right(bool val)
    {
        m_right = val;   
    }
    virtual void set_left(bool val)
    {
        m_left = val; 
    } 
    
    virtual void set_enter(bool val)
    {
        m_enter = val;    
    }
    
    virtual void set_escape(bool val)
    {
        m_escape = val;    
    }
    
    virtual void set_speed(int val)
    {
        m_speed = val;    
    }
    

    
public:
    void example_code();
    void move_foot_rfr();
    void stop_foot_rfr();
    void move_foot(int pos);
    void move_neck(int pos);
    void move_hand(int pos);
    void stop_foot();
    void stop_neck();
    void stop_hand();
    void reset_motors();
    void zero_position_foot();
    int position_foot();
    void practice();
    void getbackAuto();
    bool is_over(int pos);
};

void Crain::move_foot_rfr()
{
    c.set_speed_sp(200);
    c.run_forever();

}

void Crain::stop_foot_rfr()
{
    c.set_stop_action("hold");
    c.stop();
}

// 0~660 벗어났는지 확인
bool Crain::is_over(int pos)
{
    if(pos > 650 || pos < -10)
    {
        return true;
    }
}

void Crain::getbackAuto()
{
    a.set_speed_sp(200);
    a.set_position_sp(0);
    a.run_to_abs_pos();
    sleep(1);
    
    b.set_speed_sp(200);
    b.set_position_sp(0);
    b.run_to_abs_pos();
    sleep(1);
    
    c.set_speed_sp(200);
    c.set_position_sp(0);
    c.run_to_abs_pos();
}


void Crain::zero_position_foot()
{
    c.set_position(0);
}
void Crain::reset_motors()
{
    a.reset();
    b.reset();
    c.reset();
}

void Crain::stop_foot()
{
    //c.set_speed_sp(0);
    //c.run_forever();
    c.set_stop_action("hold");
}
void Crain::stop_neck()
{
    // b.set_speed_sp(0);
    // b.run_forever();
    b.set_stop_action("hold");
    
}
void Crain::stop_hand()
{
    // a.set_speed_sp(0);
    // a.run_forever();
    a.set_stop_action("hold");
}
void Crain::move_foot(int pos)
{
  
    c.set_position_sp(pos);
    c.set_speed_sp(get_speed());
    c.run_to_abs_pos();
   
}

void Crain::move_neck(int pos)
{

    
    b.set_position_sp(pos);
    b.set_speed_sp(get_speed_neck());
    b.run_to_abs_pos();
}

void Crain::move_hand(int pos)
{
   
   
    a.set_position_sp(pos);
    a.set_speed_sp(get_speed_hand());
    a.run_to_abs_pos();
    
}


int Crain::position_foot()
{
    return c.position();
}

int main()
{     
    Crain crain;
    double dis, position;
    int turn =0, slT = 1.5;
    //max neck= 205(short) 192(long)
    int i = 10, max_foot = 660, max_neck = 192, max_hand = 60;
   
    
    while(true)
    {
        
        if(crain.get_touch_pressed() == true)
        {
            crain.reset_motors(); //reset all motors position to 0
            
            
        for(int z = 0; z < 3; z++)
        {
            
            //scan
            while(true)
            {
                dis = crain.get_distance();
                std::cout<<"DISTANCE1: "<< dis <<std::endl;
                //position = crain.position_foot();
                //std::cout<< "POSITION         :" << position <<std::endl;
                
                
                crain.move_foot_rfr();
                if(dis < 15)
                {
                    position = crain.position_foot();
                    std::cout<< "POSITION         :" << position <<std::endl;
                    break;
                }
                
            }
            crain.stop_foot_rfr();
            sleep(slT);
            
            if(position < 440)
            {
            crain.move_foot(position-60);
            }else{
                crain.move_foot(position-30);
            }
            sleep(0.5);
            crain.move_neck(max_neck);
            sleep(slT);
            crain.move_hand(max_hand);
            sleep(slT);
            crain.move_neck(0);
            sleep(slT);
            crain.move_foot(max_foot);
            sleep(slT);
            crain.move_neck(max_neck);
            sleep(slT);
            crain.move_hand(0);
            sleep(slT);
            crain.move_neck(0);
            sleep(slT);
            crain.move_foot(150);//220으로 계속 돌아감. 
            sleep(slT);
            }
            
            
        }
    }
}
