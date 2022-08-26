#include "Render.h"
#include "../ModuleManager.h"
#include "../../Utils/Game.h"

Render::Render() : Module(VK_INSERT, "Render", "��ȾUI������") {
	setEnabled(true);
	SetKeyMode(KeyMode::Switch);
}

auto Render::onRenderDetour(MinecraftUIRenderContext* ctx)->void {
	if (isEnabled()) {
		//����� �����б�
		UIColor color = UIColor();
		RectangleArea ra = RectangleArea(100, 150, 100, 150);
		ctx->fillRectangle(ra, color, 1);
	}
}
