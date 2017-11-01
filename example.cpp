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
        return 1000;
    }
    
    virtual int get_speed_neck()
    {
        return 300;
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
        return 200;
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
    void move_foot(int pos, int flag);
    void move_neck(int pos, int flag);
    void move_hand(int pos, int flag);
    void stop_foot();
    void stop_neck();
    void stop_hand();
    int position_foot();
};

void Crain::stop_foot()
{
    c.set_speed_sp(0);
    c.run_forever();
}
void Crain::stop_neck()
{
    b.set_speed_sp(0);
    b.run_forever();
    
}
void Crain::stop_hand()
{
    a.set_speed_sp(0);
    a.run_forever();
}
void Crain::move_foot(int pos, int flag)
{
  
    if (flag == 1)
    {
        pos *= -1;
    }
    c.set_position(0);
    c.set_position_sp(pos);
    c.set_speed_sp(get_speed());
    c.run_to_abs_pos();
}

void Crain::move_neck(int pos, int flag)
{
    if (flag == 1)
    {
        pos *= -1;
    }
    b.set_position(0);
    b.set_position_sp(pos);
    b.set_speed_sp(get_speed_neck());
    b.run_to_abs_pos();
}

void Crain::move_hand(int pos, int flag)
{
    if (flag == 1)
    {
        pos *= -1;
    }
    a.set_position(0);
    a.set_position_sp(pos);
    a.set_speed_sp(get_speed_hand());
    a.set_stop_action("hold");
    a.run_to_abs_pos();
    
}

int Crain::position_foot()
{
    return c.position_sp();
}
int main()
{     
    Crain crain;
    
    while(true)
    {
        if(crain.get_touch_pressed()==true)
        { 
        // int scan = 1;
        
            for(int i = 0; i < 400; i += 10)
            {
            crain.move_foot(i, 0);
            std::cout<< crain.position_foot() <<std::endl;
            }
        
        sleep(2);
        crain.move_neck(300, 0);
        sleep(1);
        crain.move_hand(200, 0);
        sleep(1);
        crain.move_neck(300, 1);
        sleep(2);
        for(int i = 0; i < 400; i+=10)
        {
        crain.move_foot(-1*i, 0);
        }
        sleep(3);
        
        for(int i = 0; i < 200; i++)
        crain.move_hand(-1 * i, 0);
        
        
       
        
        }
    }
}
