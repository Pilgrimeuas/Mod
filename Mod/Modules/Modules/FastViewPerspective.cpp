#include "FastViewPerspective.h"
#include "../../Utils/Game.h"

FastViewPerspective::FastViewPerspective() : Module(VK_F9, "FastViewPerspective", "����Ԥ���ڶ��˳��ӽ�") {
	setEnabled(true);
}

auto FastViewPerspective::isToggle()->bool {
	return Game::IsKeyDown('R');
}