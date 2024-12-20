//
// Created by rei on 12/9/24.
//

#ifndef PROJECTDUNGEONDESPOILER_BATTLE_H
#define PROJECTDUNGEONDESPOILER_BATTLE_H
#include "../Creature.h"
#include "../CreatureLoader.h"
#include "../Scene.h"

namespace DespoilerEngine {

class BattleScene final : public Scene {
public:
  ~BattleScene() override;
  BattleScene(SDL_Window *s_window, SDL_Renderer *s_renderer, const int *p_width, const int *p_height);
  void init() override;
  void run(int &state) const override;
  void cleanUp() const override;
  void handleEvents(SDL_Event &event, bool &isRunning, int &currentIndex) const override;

private:
  mutable SDL_Texture *BgTextureBattle;
  CreatureCollection *Creatures;
  std::vector<Creature> CreaturesBattle;
};

} // namespace DespoilerEngine

#endif // PROJECTDUNGEONDESPOILER_BATTLE_H
