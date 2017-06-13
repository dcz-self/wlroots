#include <stdlib.h>
#include <string.h>
#include <wayland-server.h>
#include <wlr/types.h>
#include <wlr/common/list.h>
#include "types.h"

struct wlr_pointer *wlr_pointer_create(struct wlr_pointer_impl *impl,
		struct wlr_pointer_state *state) {
	struct wlr_pointer *pointer = calloc(1, sizeof(struct wlr_pointer));
	pointer->impl = impl;
	pointer->state = state;
	wl_signal_init(&pointer->events.motion);
	wl_signal_init(&pointer->events.motion_absolute);
	wl_signal_init(&pointer->events.button);
	wl_signal_init(&pointer->events.axis);
	return pointer;
}

void wlr_pointer_destroy(struct wlr_pointer *kb) {
	if (!kb) return;
	kb->impl->destroy(kb->state);
	free(kb);
}
