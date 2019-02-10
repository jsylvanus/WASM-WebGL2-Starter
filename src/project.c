#include "stdlib.h"
#include "emscripten.h"
#include "emscripten/html5.h"
#include "GL/gl.h"
#include "GL/glew.h"

const char* canvasId = "screen";

static int winWidth;
static int winHeight;

void update_canvas() {
	double width, height;
	emscripten_get_element_css_size(canvasId, &width, &height);
	winWidth = (int)width;
	winHeight = (int)height;
	emscripten_set_canvas_element_size(canvasId, winWidth, winHeight);
}

EM_BOOL emsc_canvas_resized(int etype, const EmscriptenUiEvent* evt, void* userData) {
	(void)etype;
	(void)evt;
	(void)userData;
	update_canvas();
}

EMSCRIPTEN_WEBGL_CONTEXT_HANDLE gl;

EM_BOOL render_frame(double time, void* userdata) {
	(void)userdata; (void)time;

	glViewport(0,0,winWidth,winHeight);
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);

	return EM_TRUE;
}

int main(void) {
	emscripten_set_resize_callback(NULL, NULL, 0, emsc_canvas_resized);
	update_canvas();

	EmscriptenWebGLContextAttributes ctxattr;
	emscripten_webgl_init_context_attributes(&ctxattr);
	ctxattr.majorVersion = 2;

	gl = emscripten_webgl_create_context(canvasId, &ctxattr);
	if (gl < 0) {
		emscripten_console_log("Failed to create webgl2 context");
		return EXIT_FAILURE;
	}
	emscripten_webgl_make_context_current(gl);

	emscripten_request_animation_frame_loop(render_frame, NULL);

	emscripten_console_log("app initialized");
	return EXIT_SUCCESS;
}

