#define SANDBOX_TRIANGLE                  0
#define SANDBOX_SQUARE                    1
#define SANDBOX_CUBE                      3
#define SANDBOX_TRIANGLE_STRIDE           3*sizeof(float)
#define SANDBOX_SQUARE_STRIDE             3*sizeof(float)
#define SANDBOX_CUBE_STRIDE               3*sizeof(float)
#define SANDBOX_TRIANGLE_OFFEST           (void*)0
#define SANDBOX_SQUARE_OFFEST             (void*)0
#define SANDBOX_CUBE_OFFEST               (void*)0
#define SANDBOX_TRIANGLE_VERTICES_COUNT   3;
#define SANDBOX_SQUARE_VERTICES_COUNT     6;
#define SANDBOX_CUBE_VERTICES_COUNT       36;
#define SANDBOX_TRIANGLE_VERTICES         {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f}
#define SANDBOX_SQUARE_VERTICES           {0.5f,  0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f}
#define SANDBOX_CUBE_VERTICES             {-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.5f,  0.5f,  0.5f,  1.0f, 1.0f, -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.5f, -0.5f,  0.5f,  1.0f, 0.0f, -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, -0.5f,  0.5f, -0.5f,  0.0f, 1.0f}

class UBufferGeometry {
    public:
        // type must be one of SANDBOX_TRIANGLE, SANDBOX_SQUARE, SANDBOX_CUBE
        UBufferGeometry(unsigned int type = SANDBOX_TRIANGLE) : type_(type) {
            initGeometry();
        }
    protected:
        void initGeometry() {
            switch(type_) {
                case SANDBOX_TRIANGLE:  
                    stride_ = SANDBOX_TRIANGLE_STRIDE;
                    vert_count_ = SANDBOX_TRIANGLE_VERTICES_COUNT;
                    offset_ = SANDBOX_TRIANGLE_OFFEST;
                    vertices = SANDBOX_TRIANGLE_VERTICES;
                    break;
                case SANDBOX_SQUARE:  
                    stride_ = SANDBOX_SQUARE_STRIDE;
                    vert_count_ = SANDBOX_SQUARE_VERTICES_COUNT;
                    offset_ = SANDBOX_SQUARE_OFFEST;
                    vertices = SANDBOX_SQUARE_VERTICES;
                    break;
                case SANDBOX_CUBE:  
                    stride_ = SANDBOX_CUBE_STRIDE;
                    vert_count_ = SANDBOX_CUBE_VERTICES_COUNT;
                    offset_ = SANDBOX_CUBE_OFFEST;
                    vertices = SANDBOX_CUBE_VERTICES;
                    break;
            }
        }
        unsigned int type_, stride_, vert_count_;
        std::vector<float> vertices = SANDBOX_TRIANGLE_VERTICES;
        void* offset_;
};