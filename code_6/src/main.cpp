#include "utils.h"
#include<vector>
#include<iostream>
#include <cmath>

using namespace std;

#define  GLM_FORCE_RADIANS
#define  GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>


//Globals
int screen_width = 640, screen_height=640;
GLint vModel_uniform, vView_uniform, vProjection_uniform;
GLint vColor_uniform,light_pos_value,light_color_value,cam_pos_value;
glm::mat4 modelT, viewT, projectionT;//The model, view and projection transformations

double oldX, oldY, currentX, currentY;
bool isDragging=false;

void createCubeObject(unsigned int &, unsigned int &);

void setupModelTransformation(unsigned int &);
void setupViewTransformation(unsigned int &);
void setupProjectionTransformation(unsigned int &);
glm::vec3 getTrackBallVector(double x, double y);
glm::vec3 camPosition,target;
float PI = 3.1415926;
float phi = PI/4, theta = PI/2;
float my_get_radius(){
    float dx = camPosition[0] - target[0];
    float dy = camPosition[1] - target[1];
    float dz = camPosition[2] - target[2];
    return sqrt(dx*dx + dy*dy + dz*dz);
}
void my_scale(float my_scale_factor){
    camPosition[0] = (camPosition[0] - target[0])*my_scale_factor + target[0];
    camPosition[1] = (camPosition[1] - target[1])*my_scale_factor + target[1];
    camPosition[2] = (camPosition[2] - target[2])*my_scale_factor + target[2];
}
void my_rotate(int option, float radians){

    radians/=40;
    if(0==option){
        theta+=radians;
    }
    else{
        phi+=radians/2;
    }   

    glm::vec3 temp;
    temp[0] = sin(-phi) * cos(-theta) * my_get_radius();
    temp[2] = sin(-phi) * sin(-theta) * my_get_radius();
    temp[1] = cos(phi) * my_get_radius();

    for(int i=0;i<3;i++) camPosition[i] = temp[i] + target[i];

}
int main(int, char**)
{
    // Setup window
    GLFWwindow *window = setupWindow(screen_width, screen_height);
    ImGuiIO& io = ImGui::GetIO(); // Create IO object

    ImVec4 clearColor = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
    camPosition = glm::vec4(0, 7.07106 * 10, 7.07106 * 10, 1.0);
    target = glm::vec4(0, 0, 0, 1.0);

    unsigned int shaderProgram = createProgram("./shaders/vshader.vs", "./shaders/fshader.fs");

    //Get handle to color variable in shader
    vColor_uniform = glGetUniformLocation(shaderProgram, "vColor");
    if(vColor_uniform == -1){
        fprintf(stderr, "Could not bind location: vColor\n");
        exit(0);
    }

    light_pos_value = glGetUniformLocation(shaderProgram, "light_pos");
    if(light_pos_value == -1){
        fprintf(stderr, "Could not bind location: light_pos\n");
        exit(0);
    }

    light_color_value = glGetUniformLocation(shaderProgram, "light_color");
    if(light_color_value == -1){
        fprintf(stderr, "Could not bind location: light_color\n");
        exit(0);
    }

    cam_pos_value = glGetUniformLocation(shaderProgram, "cam_pos");
    if(cam_pos_value == -1){
        fprintf(stderr, "Could not bind location: cam_pos\n");
        exit(0);
    }

    glUseProgram(shaderProgram);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    setupModelTransformation(shaderProgram);
    setupViewTransformation(shaderProgram);
    setupProjectionTransformation(shaderProgram);

    createCubeObject(shaderProgram, VAO);

    oldX = oldY = currentX = currentY = 0.0;
    int prevLeftButtonState = GLFW_RELEASE;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();


        if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_LeftArrow))) {
          // strcpy(textKeyStatus, "Key status: Left");
          my_rotate(0,-1);
          setupViewTransformation(shaderProgram);
          // setupModelTransformationAxis(shaderProgram, glm::radians(10.0), glm::vec3(1, 0, 0));
        }
        else if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_RightArrow))) {
          // strcpy(textKeyStatus, "Key status: Right");
          my_rotate(0,1);
          setupViewTransformation(shaderProgram);
          // setupModelTransformationAxis(shaderProgram, glm::radians(20.0), glm::vec3(1, 0, 0));
        }
        else if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_UpArrow))) {
          if(io.KeyShift){
            // strcpy(textKeyStatus, "Key status: Shift + Up");
            my_scale((my_get_radius() + 1)/my_get_radius());
            setupViewTransformation(shaderProgram);
          }
          else{
            // strcpy(textKeyStatus, "Key status: Up");
            // camPosition.y+=1;
            my_rotate(1,1);
            setupViewTransformation(shaderProgram);
          }
        }
        else if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_DownArrow))) {
          if(io.KeyShift){
            // strcpy(textKeyStatus, "Key status: Shift + Down");
            my_scale((max(my_get_radius() - 1, (float)0.1))/my_get_radius());
            setupViewTransformation(shaderProgram);
          }
          else {
            // strcpy(textKeyStatus, "Key status: Down");
            // camPosition.y+=-1;
            my_rotate(1,-1);
            setupViewTransformation(shaderProgram);
          }
        }


        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glUseProgram(shaderProgram);

        {
            ImGui::Begin("Information");                          
            ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }



        ImGui::Begin("Switch Mode");
        if (ImGui::Button("Input A")) {
            camPosition[0] = 0;
            camPosition[1] = 7.07106 * 10;
            camPosition[2] = 7.07106 * 10;
            target[0] = 0;
            target[1] = 0;
            target[2] = 0;
            phi = PI/4;
            theta = PI/2;
            setupViewTransformation(shaderProgram);
        }  
        if (ImGui::Button("Input B")) {
            camPosition[0] = 1000;
            camPosition[1] = 7.07106 * 10;
            camPosition[2] = 7.07106 * 10;
            target[0] = 1000;
            target[1] = 0;
            target[2] = 0;
            phi = PI/4;
            theta = PI/2;
            setupViewTransformation(shaderProgram);
        }  
        if (ImGui::Button("Output A")) {
            camPosition[0] = 2000;
            camPosition[1] = 7.07106 * 10;
            camPosition[2] = 7.07106 * 10;
            target[0] = 2000;
            target[1] = 0;
            target[2] = 0;
            phi = PI/4;
            theta = PI/2;
            setupViewTransformation(shaderProgram);
        } 
        if (ImGui::Button("Output B")) {
            camPosition[0] = 3000;
            camPosition[1] = 7.07106 * 10;
            camPosition[2] = 7.07106 * 10;
            target[0] = 3000;
            target[1] = 0;
            target[2] = 0;
            phi = PI/4;
            theta = PI/2;
            setupViewTransformation(shaderProgram);
        } 
        ImGui::End();
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(VAO); 
        
        glUniform3f(vColor_uniform, 0.5, 0.5, 0.5);
        glUniform3f(light_pos_value, 1500, 100.0, 0.0);
        glUniform3f(light_color_value, 1.0, 0.0, 0.0);
        glUniform3f(cam_pos_value, camPosition.x, camPosition.y, camPosition.z);
        glDrawArrays(GL_TRIANGLES, 0, 500 * 500 * 2);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

    }

    // Cleanup
    cleanup(window);

    return 0;
}
int n = 101;
class PLANE
{
private:
    int x_offset;
    vector<double> points;
    double func(int mode,int i,int j)
    {
        if(0==mode) return 1;
        i-=n/2;
        j-=n/2;
        double val = cos(i/4.0)*cos(j/4.0);
        val+=1;
        val/=2;
        val = 1-val;
        val*=10;
        return 1 + val;
    }
public:
    PLANE()
    {

    }
    void set_offset(int a)
    {
        this->x_offset = a;
    }
    void fill_points(int mode)
    {
        this->points = vector<double>();
        for(int i=0;i<n-1;i++)
        {
            for(int j=0;j<n-1;j++)
            {
                points.push_back((j) - n/2 + x_offset); 
                points.push_back(func(mode,i+1,j));
                points.push_back((i + 1) - n/2); 

                points.push_back((j + 1) - n/2 + x_offset); 
                points.push_back(func(mode,i+1,j+1));
                points.push_back((i + 1) - n/2); 

                points.push_back((j + 1) - n/2 + x_offset); 
                points.push_back(func(mode,i,j+1));
                points.push_back((i) - n/2); 


                points.push_back((j) - n/2 + x_offset); 
                points.push_back(func(mode,i+1,j));
                points.push_back((i + 1) - n/2); 

                points.push_back((j + 1) - n/2 + x_offset); 
                points.push_back(func(mode,i,j+1));
                points.push_back((i) - n/2); 

                points.push_back((j) - n/2 + x_offset); 
                points.push_back(func(mode,i,j));
                points.push_back((i) - n/2); 

            }
        }
    }
    vector<double> get_points()
    {
        return this->points;
    }
    vector<vector<double>> get_analogy(PLANE *p)
    {
        vector<vector<double>> analogy(n, vector<double>(n));
        vector<double> points_of_p = p->get_points();
        for(int i=0;i<points.size();i+=3)
        {
            analogy[points[i] + n/2 - x_offset][points[i + 2] + n/2] = points_of_p[i + 1] - points[i + 1];
        }
        return analogy;
    }

};
class CYLINDER
{
private:
    double PI = 3.1415926;
    int x_offset;
    double Radius, height;
    vector<double> points_curve,points_caps;
    int total_theta_steps = 46;
    int total_z_steps = 31;
    vector<vector<double>> analogy;
    float get_theta_angle(int theta_step)
    {
        return theta_step*(2*PI)/(total_theta_steps);
    }
    double get_z_val(double val)
    {
        val = val-15;
        val*=(height/(total_z_steps-1));
        return val;
    }
public:
    void set_offset(int a)
    {
        this->x_offset = a;
    }
    void set_radius(double a)
    {
        this->Radius = a;
    }
    void set_height(double a)
    {
        this->height = a;
    }
    double X(int mode, double theta,double z)
    {
        double R = Radius;
        if(2==mode)
        {
            float u = ((z * ((total_z_steps - 1)/height)) + 15) / (total_z_steps);
            float v = theta/(2 * PI);
            u*=101;
            v*=101;
            int ii = int(u);
            int jj = int(v);
            ii%=101;
            jj%=101;
            R+=(this->analogy[ii][jj]);
        }
        return R * cos(theta);
    }
    double Y(int mode, double theta, double z)
    {
        double R = Radius;
        if(2==mode)
        {
            float u = ((z * ((total_z_steps - 1)/height)) + 15) / (total_z_steps);
            float v = theta/(2 * PI);
            u*=101;
            v*=101;
            int ii = int(u);
            int jj = int(v);
            ii%=101;
            jj%=101;
            R+=(this->analogy[ii][jj]);
        }
        return R * sin(theta);
    }
    void fill_points(int mode)
    {
        for(int theta_step = 0;theta_step<total_theta_steps;theta_step++)
        {
            points_caps.push_back(x_offset);
            points_caps.push_back(get_z_val(30));
            points_caps.push_back(0);

            points_caps.push_back(x_offset + X(mode,get_theta_angle((theta_step + 1)%total_theta_steps),get_z_val(30)));
            points_caps.push_back(get_z_val(30));
            points_caps.push_back(Y(mode,get_theta_angle((theta_step + 1)%total_theta_steps),get_z_val(30)));

            points_caps.push_back(x_offset + X(mode,get_theta_angle((theta_step)%total_theta_steps),get_z_val(30)));
            points_caps.push_back(get_z_val(30));
            points_caps.push_back(Y(mode,get_theta_angle((theta_step)%total_theta_steps),get_z_val(30)));



        }

        for(int theta_step = 0;theta_step<total_theta_steps;theta_step++)
        {


            points_caps.push_back(x_offset);
            points_caps.push_back(get_z_val(0));
            points_caps.push_back(0);

            points_caps.push_back(x_offset + X(mode,get_theta_angle((theta_step + 1)%total_theta_steps),get_z_val(0)));
            points_caps.push_back(get_z_val(0));
            points_caps.push_back(Y(mode,get_theta_angle((theta_step + 1)%total_theta_steps),get_z_val(0)));

            points_caps.push_back(x_offset + X(mode,get_theta_angle((theta_step)%total_theta_steps),get_z_val(0)));
            points_caps.push_back(get_z_val(0));
            points_caps.push_back(Y(mode,get_theta_angle((theta_step)%total_theta_steps),get_z_val(0)));

        }

        for(int z_step = 1;z_step<total_z_steps;z_step++)
        {
            for(int theta_step = 0;theta_step<total_theta_steps;theta_step++)
            {
                points_curve.push_back(x_offset + X(mode,get_theta_angle((theta_step)%total_theta_steps),get_z_val(z_step-1)));
                points_curve.push_back(get_z_val(z_step-1));
                points_curve.push_back(Y(mode,get_theta_angle((theta_step)%total_theta_steps),get_z_val(z_step-1)));

                points_curve.push_back(x_offset + X(mode,get_theta_angle((theta_step)%total_theta_steps),get_z_val(z_step)));
                points_curve.push_back(get_z_val(z_step));
                points_curve.push_back(Y(mode,get_theta_angle((theta_step)%total_theta_steps),get_z_val(z_step)));


                points_curve.push_back(x_offset + X(mode,get_theta_angle((theta_step + 1)%total_theta_steps),get_z_val(z_step)));
                points_curve.push_back(get_z_val(z_step));
                points_curve.push_back(Y(mode,get_theta_angle((theta_step + 1)%total_theta_steps),get_z_val(z_step)));

                points_curve.push_back(x_offset + X(mode,get_theta_angle((theta_step + 1)%total_theta_steps),get_z_val(z_step)));
                points_curve.push_back(get_z_val(z_step));
                points_curve.push_back(Y(mode,get_theta_angle((theta_step + 1)%total_theta_steps),get_z_val(z_step)));


                points_curve.push_back(x_offset + X(mode,get_theta_angle((theta_step + 1)%total_theta_steps),get_z_val(z_step-1)));
                points_curve.push_back(get_z_val(z_step-1));
                points_curve.push_back(Y(mode,get_theta_angle((theta_step + 1)%total_theta_steps),get_z_val(z_step-1)));

                points_curve.push_back(x_offset + X(mode,get_theta_angle((theta_step)%total_theta_steps),get_z_val(z_step-1)));
                points_curve.push_back(get_z_val(z_step-1));
                points_curve.push_back(Y(mode,get_theta_angle((theta_step)%total_theta_steps),get_z_val(z_step-1)));

            }
        }

    }
    void set_analogy(const vector<vector<double>> a)
    {
        this->analogy = a;
    }
    vector<double> get_points_caps()
    {
        return this->points_caps;
    }
    vector<double> get_points_curve()
    {
        return this->points_curve;
    }
    vector<double> get_points()
    {
        vector<double> temp;
        for(double x:points_curve)
        {
            temp.push_back(x);
        }
        for(double x:points_caps)
        {
            temp.push_back(x);
        }
        return temp;
    }
};
void createCubeObject(unsigned int &program, unsigned int &cube_VAO)
{
    glUseProgram(program);

    //Bind shader variables
    int vVertex_attrib = glGetAttribLocation(program, "vVertex");
    if(vVertex_attrib == -1) {
        fprintf(stderr, "Could not bind location: vVertex\n");
        exit(0);
    }


    //Generate VAO object
    glGenVertexArrays(1, &cube_VAO);
    glBindVertexArray(cube_VAO);

    //Create VBOs for the VAO
    //Position information (data + format)
    int nVertices = 500 * 500 * 2 * 3; //(6 faces) * (2 triangles each) * (3 vertices each)
    GLfloat *expanded_vertices = new GLfloat[nVertices*3];
    vector<double> points;


    PLANE *plane_1 = new PLANE();
    plane_1->set_offset(0);
    plane_1->fill_points(0);


    PLANE *plane_2 = new PLANE();
    plane_2->set_offset(1000);
    plane_2->fill_points(1);


    vector<vector<double>> input_analogy = plane_1->get_analogy(plane_2);



    CYLINDER *cylinder_1 = new CYLINDER();
    cylinder_1->set_offset(2000);
    cylinder_1->set_radius(18);
    cylinder_1->set_height(40);
    cylinder_1->fill_points(0);



    CYLINDER *cylinder_2 = new CYLINDER();
    cylinder_2->set_offset(3000);
    cylinder_2->set_radius(18);
    cylinder_2->set_height(40);
    cylinder_2->set_analogy(input_analogy);
    cylinder_2->fill_points(2);





    int index = 0;
    points = plane_1->get_points();
    for(int i=0;i<points.size();i++)
    {
        expanded_vertices[index++] = points[i];
    }
    points = plane_2->get_points();
    for(int i=0;i<points.size();i++)
    {
        expanded_vertices[index++] = points[i];
    }
    points = cylinder_1->get_points();
    for(int i=0;i<points.size();i++)
    {
        expanded_vertices[index++] = points[i];
    }
    points = cylinder_2->get_points();
    for(int i=0;i<points.size();i++)
    {
        expanded_vertices[index++] = points[i];
    }




    GLfloat *normals = new GLfloat[nVertices*3];

    for(int i=0;i<nVertices*3;i+=9){
        glm::vec3 p1 = {expanded_vertices[i], expanded_vertices[i + 1],expanded_vertices[i + 2]};
        glm::vec3 p2 = {expanded_vertices[i + 3], expanded_vertices[i + 4],expanded_vertices[i + 5]};
        glm::vec3 p3 = {expanded_vertices[i + 6], expanded_vertices[i + 7],expanded_vertices[i + 8]};

        glm::vec3 v1 = p1 - p3;
        glm::vec3 v2 = p2 - p3;

        v1 = glm::normalize(v1);
        v2 = glm::normalize(v2);
        glm::vec3 v3 = glm::cross(v1,v2);
        v3 = glm::normalize(v3);
        // if(dot(v3, p1) < 0 || dot(v3, p2) < 0 || dot(v3, p3) < 0) v3*=-1;
        for(int j=0;j<9;j++){
            normals[j + i] = v3[j%3];
        }
    }

























    GLuint vertex_VBO;
    glGenBuffers(1, &vertex_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO);
    glBufferData(GL_ARRAY_BUFFER, nVertices*3*sizeof(GLfloat), expanded_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vVertex_attrib);
    glVertexAttribPointer(vVertex_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);



    GLuint normal_VBO;
    glGenBuffers(1, &normal_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, normal_VBO);
    glBufferData(GL_ARRAY_BUFFER, nVertices*3*sizeof(GLfloat), normals, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);





    delete []expanded_vertices;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); //Unbind the VAO to disable changes outside this function.
}

void setupModelTransformation(unsigned int &program)
{
    //Modelling transformations (Model -> World coordinates)
    modelT = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));//Model coordinates are the world coordinates

    //Pass on the modelling matrix to the vertex shader
    glUseProgram(program);
    vModel_uniform = glGetUniformLocation(program, "vModel");
    if(vModel_uniform == -1){
        fprintf(stderr, "Could not bind location: vModel\n");
        exit(0);
    }
    glUniformMatrix4fv(vModel_uniform, 1, GL_FALSE, glm::value_ptr(modelT));
}


void setupViewTransformation(unsigned int &program)
{
    //Viewing transformations (World -> Camera coordinates
    //Camera at (0, 0, 100) looking down the negative Z-axis in a right handed coordinate system
    viewT = glm::lookAt(glm::vec3(camPosition), glm::vec3(target), glm::vec3(0.0, 1.0, 0.0));

    //Pass-on the viewing matrix to the vertex shader
    glUseProgram(program);
    vView_uniform = glGetUniformLocation(program, "vView");
    if(vView_uniform == -1){
        fprintf(stderr, "Could not bind location: vView\n");
        exit(0);
    }
    glUniformMatrix4fv(vView_uniform, 1, GL_FALSE, glm::value_ptr(viewT));
}

void setupProjectionTransformation(unsigned int &program)
{
    //Projection transformation
    projectionT = glm::perspective(45.0f, (GLfloat)screen_width/(GLfloat)screen_height, 0.1f, 1000.0f);

    //Pass on the projection matrix to the vertex shader
    glUseProgram(program);
    vProjection_uniform = glGetUniformLocation(program, "vProjection");
    if(vProjection_uniform == -1){
        fprintf(stderr, "Could not bind location: vProjection\n");
        exit(0);
    }
    glUniformMatrix4fv(vProjection_uniform, 1, GL_FALSE, glm::value_ptr(projectionT));
}

glm::vec3 getTrackBallVector(double x, double y)
{
	glm::vec3 p = glm::vec3(2.0*x/screen_width - 1.0, 2.0*y/screen_height - 1.0, 0.0); //Normalize to [-1, +1]
	p.y = -p.y; //Invert Y since screen coordinate and OpenGL coordinates have different Y directions.

	float mag2 = p.x*p.x + p.y*p.y;
	if(mag2 <= 1.0f)
		p.z = sqrtf(1.0f - mag2);
	else
		p = glm::normalize(p); //Nearest point, close to the sides of the trackball
	return p;
}

