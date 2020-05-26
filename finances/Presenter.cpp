#include "Presenter.hpp"

namespace finances {
Presenter::Presenter(View &view) : view{view} {}

static void show(View &view, const Transaction &t) { view.show({t}); }

void Presenter::verified(const Transaction &t) { show(view, t); }

void Presenter::added(const Transaction &t) { show(view, t); }
}
