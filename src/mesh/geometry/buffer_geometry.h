#define SANDBOX_TRIANGLE 0
#define SANDBOX_SQUARE 1
#define SANDBOX_CUBE 3
#define SANDBOX_TRIANGLE_STRIDE 3*sizeof(float)
#define SANDBOX_SQUARE_STRIDE 3*sizeof(float)
#define SANDBOX_CUBE_STRIDE 3*sizeof(float)
#define SANDBOX_TRIANGLE_OFFEST (void*)0
#define SANDBOX_SQUARE_OFFEST (void*)0
#define SANDBOX_CUBE_OFFEST (void*)0
#define SANDBOX_TRIANGLE_VERTICES_COUNT 3;
#define SANDBOX_SQUARE_VERTICES_COUNT 6;
#define SANDBOX_CUBE_VERTICES_COUNT 36;

class BufferGeometry {
    public:
        BufferGeometry() {}
};