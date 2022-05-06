#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"

class TextObject {
public:
    TextObject();
    ~TextObject();
    enum TextColor {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
    };
    // Chon tat ca
    void Set (int x, int y, const std::string& text, int type_color);

    // Chon vi tri
    void SetRect (int x, int y) { text_rect.x = x; text_rect.y = y; }

    // Chon noi dung
    void SetText (const std::string& text) {str_val_ = text;}

    // Chon Mau
    void SetColor (Uint8 red, Uint8 green, Uint8 blue); // Chọn được mọi loại màu
    void SetColor (int type); // Chọn các màu cơ bản đã tạo

    // Cap nhat text
    bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);

    // In chu ra man hinh
    void RenderText(SDL_Renderer* screen, 
                    /*int xp, int yp,*/
                    SDL_Rect* clip = NULL, 
                    double angle = 0.0, 
                    SDL_Point* center = NULL, 
                    SDL_RendererFlip flip = SDL_FLIP_NONE);  

    // Giai phong
    void Free();
    
    // Lay so do
    SDL_Rect GetRect () {return text_rect;}
    int GetWidth() const {return text_rect.w;}
    int GetHeight() const {return text_rect.h;}

    // Lay noi dung
    std::string GetText() const {return str_val_;}
    
private:
    // Noi dung
    std::string str_val_;

    // Mau
    SDL_Color text_color_;

    // So do
    SDL_Rect text_rect;
    
    SDL_Texture* texture_;

};
#endif