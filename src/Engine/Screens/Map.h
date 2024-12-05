//
// Created by rei on 12/5/24.
//

#ifndef MAP_H
#define MAP_H
#include "../Scene.h"
#include "../Game.h"

namespace DespoilerEngine {

class Map final : public Scene{
public:
  ~Map() override = default;
  Map(const char *p_title, int p_w, int p_h);
  Map(const std::string &p_title, int p_w, int p_h);
  void init() override;
  void run(int &state) const override;
  void clear() const override;
  void cleanUp() const override;
  void handleEvents(SDL_Event &event, bool &isRunning,
                    int &currentIndex) const override;

private:
  SDL_Texture *BgTextureMain;
};

inline auto map_window = new Map(*Title,SCREEN_WIDTH, SCREEN_HEIGHT);

} // DespoilerEngine

#endif //MAP_H