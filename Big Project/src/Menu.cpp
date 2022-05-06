#include "Menu.h"

void Menu::Load (SDL_Renderer* des){
    background.LoadImage("Assets\\Menu\\Start_menu_2.png", des);
}

int Menu::Show(SDL_Renderer* des, TTF_Font* font[]) {
  // Nút bấm Menu
  const int kMenuItemNum = 2;

  TextObject text_menu[kMenuItemNum];
  text_menu[0].SetText ("Play game");
  text_menu[0].SetColor(TextObject::BLACK_TEXT);
  text_menu[0].SetRect(200, 250);

  text_menu[1].SetText ("Exit");
  text_menu[1].SetColor(TextObject::BLACK_TEXT);
  text_menu[1].SetRect(200, 350);

  // text_menu[2].SetText ("Rule");
  // text_menu[2].SetColor(TextObject::BLACK_TEXT);
  // text_menu[2].SetRect(200, 300);

  bool selected[kMenuItemNum] = {};

  // Toa do chuot
  int xm (0), ym (0);
  SDL_Event m_event;

  // Hiển thị Menu
  while(true){
    // Ảnh nền Menu
    background.SetRect(0, 0);
    background.Render(des, NULL);

    TextObject game_name;
    game_name.Set (50, 50, "Sword Man", TextObject::RED_TEXT);
    game_name.LoadFromRenderText(font[2], des);
    game_name.RenderText(des);

    // Render text
    for(int i = 0; i < kMenuItemNum; i ++)
    {
      text_menu[i].LoadFromRenderText(font[1], des);
      text_menu[i].RenderText(des);
    }

    // Kiểm tra sự kiện chuột
    while (SDL_PollEvent(&m_event))
    {
      switch(m_event.type)
      {
        // Bam nut X goc phai thoat chuong trinh
        case SDL_QUIT:
          return 1;

        // Con chuot di chuyen
        case SDL_MOUSEMOTION:
        {
          // Lay toa do con chuot
          xm = m_event.motion.x;
          ym = m_event.motion.y;
          // Kiem tra toa do chuot co dang o trong nut bam khong
          for (int i = 0; i < kMenuItemNum; i++) 
          {
            if (SDLCommonFunc::CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
            {
              if (selected[i] == false) 
              {
                // Doi trang thai
                selected[i] = true;
                // Doi mau
                text_menu[i].SetColor(TextObject::RED_TEXT);
              }
            } 
            else  
            {
              if (selected[i] == true)
              {
                selected[i] = 0;
                text_menu[i].SetColor(TextObject::BLACK_TEXT);
              }
            }
          }
        }
          break;

        // Bam chuot
        case SDL_MOUSEBUTTONDOWN:
        {
          xm = m_event.button.x;
          ym = m_event.button.y;
          for (int i = 0; i < kMenuItemNum; i++)
          {
            if (SDLCommonFunc::CheckFocusWithRect(xm, ym, text_menu[i].GetRect())) return i;
          }

        }
          break;

        case SDL_KEYDOWN:
          if(m_event.key.keysym.sym == SDLK_ESCAPE) return 1;

        default:
          break;
      }
    }
    SDL_RenderPresent(des);
  }

  return 1;
}
