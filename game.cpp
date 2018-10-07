#include "game.h"

game::game()
{
    m_game_state=gs_init;
}

bool game::init(int* window_size,bool* pKeys_real,bool* pKeys_translated,
                int* pMouse_pos,bool* pMouse_but,bool reinit)
{
    cout<<"Game: Initialization\n";

    m_window_size[0]=window_size[0];
    m_window_size[1]=window_size[1];
    m_pKeys_real=pKeys_real;
    m_pKeys_translated=pKeys_translated;
    m_pMouse_pos=pMouse_pos;
    m_pMouse_but=pMouse_but;

    //load textures and sound
    if(!reinit)
    {
        //texture
        if(!load_textures())
        {
            return false;
        }

        //sound
        if(!load_sounds())
        {
            return false;
        }
    }

    //init gamepads and players
    for(int i=0;i<4;i++)
    {
        m_gamepad[i]=gamepad(i);
        if( m_gamepad[i].IsConnected() )
         m_gamepad_connected[i]=true;
        else
         m_gamepad_connected[i]=false;
    }

    m_key_rerouter.init(m_pKeys_real,m_pKeys_translated);


    m_game_state=gs_menu;

    cout<<"Game: Initialization complete\n";

    return true;
}

bool game::update(bool& quit_flag)
{
    //get gamepad data
    st_gamepad_data gamepad_data[4];
    for(int gamepad_i=0;gamepad_i<4;gamepad_i++)
    {
        if( m_gamepad[gamepad_i].IsConnected() )
        {
            //test if new connection
            if(!m_gamepad_connected[gamepad_i])
            {
                cout<<"Gamepad: New controller conencted: "<<gamepad_i+1<<endl;
            }

            m_gamepad_connected[gamepad_i]=true;
        }
        else//lost controller
        {
            if( m_gamepad_connected[gamepad_i] )//had connection and lost it
            {
                m_gamepad_connected[gamepad_i]=false;
                cout<<"Gamepad: Lost connection to controller: "<<gamepad_i+1<<endl;
            }
        }
    }

    //update key rerouter
    m_key_rerouter.update();

    switch(m_game_state)
    {
        case gs_init:
        {
            //nothing
        }break;

        case gs_menu:
        {
            //nothing
        }break;

        case gs_in_game:
        {
            //nothing
        }break;
    }

    return true;
}

bool game::draw(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    //glLoadIdentity();

    switch(m_game_state)
    {
        case gs_init:
        {
            //nothing
        }break;

        case gs_menu:
        {
            //nothing
        }break;

        case gs_in_game:
        {
            //nothing
        }break;
    }

    return true;
}


//Private

bool game::load_textures(void)
{
    cout<<"Game: Loading texture\n";

    m_tex_temp=SOIL_load_OGL_texture
    (
        "data\\texture\\texture.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        /*SOIL_FLAG_INVERT_Y | */SOIL_FLAG_COMPRESS_TO_DXT
    );

    if(m_tex_temp==0)
    {
        cout<<"ERROR: Could not load texture\n";
        return false;
    }

    return true;
}

bool game::load_sounds(void)
{
    cout<<"Game: Loading sound\n";

    m_pSound=new sound();

    bool error_flag=false;

    if( !m_pSound->load_WAVE_from_file( wav_beep1,"data\\sound\\beep1.wav" ) ) error_flag=true;

    if(error_flag)
    {
        cout<<"ERROR: Could not load sound\n";
        return false;
    }

    return true;
}
