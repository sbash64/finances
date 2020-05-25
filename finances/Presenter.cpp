#include "Presenter.hpp"

namespace finances {
Presenter::Presenter(Model &record, View &printer) : view{printer} {
    record.subscribe(this);
}

static void show(View &view, const Transaction &t) { view.show({t}); }

void Presenter::verified(const Transaction &t) { show(view, t); }

void Presenter::added(const Transaction &t) { show(view, t); }
}
