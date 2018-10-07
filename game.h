#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SOIL/SOIL.h>
#include <gl/gl.h>
#include <string>
#include <vector>


#include "sound.h"
#include "gamepad.h"
#include "key_reroute.h"

enum game_states
{
    gs_init=0,
    gs_menu,
    gs_in_game
};

class game
{
    public:

        game();

        bool init(int* pWindow_size,bool* pKeys_real,bool* pKeys_translated,
                  int* pMouse_pos,bool* pMouse_but,bool reinit=false);
        bool update(bool& quit_flag);
        bool draw(void);

    private:

        int   m_game_state;
        int   m_window_size[2];
        bool* m_pKeys_real;
        bool* m_pKeys_translated;
        int*  m_pMouse_pos;
        bool* m_pMouse_but;
        bool  m_gamepad_connected[4];

        //texture
        int   m_tex_temp;

        //object
        key_reroute m_key_rerouter;
        sound*      m_pSound;
        gamepad     m_gamepad[4];

        bool  load_textures(void);
        bool  load_sounds(void);
};

#endif // GAME_H
