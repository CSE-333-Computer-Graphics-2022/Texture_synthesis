//Assignment 03: Lighting and shading

/*References
  Trackball: http://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Arcball
*/

#include "utils.h"
#include<vector>
#include<iostream>

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
    // return sqrt(camPosition.x * camPosition.x + camPosition.y * camPosition.y + camPosition.z * camPosition.z);
    return sqrt(dx*dx + dy*dy + dz*dz);
}
void my_scale(float my_scale_factor){
    camPosition[0] = (camPosition[0] - target[0])*my_scale_factor + target[0];
    camPosition[1] = (camPosition[1] - target[1])*my_scale_factor + target[1];
    camPosition[2] = (camPosition[2] - target[2])*my_scale_factor + target[2];
    // camPosition[1]*=my_scale_factor;
    // camPosition[2]*=my_scale_factor;
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
        // camPosition[1]*=-1;

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

        // Get current mouse position
        // int leftButtonState = glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT);
        // double x,y;
        // glfwGetCursorPos(window,&x,&y);
        // if(leftButtonState == GLFW_PRESS && prevLeftButtonState == GLFW_RELEASE){
        //     isDragging = true;
        //     currentX = oldX = x;
        //     currentY = oldY = y;
        // }
        // else if(leftButtonState == GLFW_PRESS && prevLeftButtonState == GLFW_PRESS){
        //     currentX = x;
        //     currentY = y;
        // }
        // else if(leftButtonState == GLFW_RELEASE && prevLeftButtonState == GLFW_PRESS){
        //     isDragging = false;
        // }

        // // Rotate based on mouse drag movement
        // prevLeftButtonState = leftButtonState;
        // if(isDragging && (currentX !=oldX || currentY != oldY))
        // {
        //     glm::vec3 va = getTrackBallVector(oldX, oldY);
        //     glm::vec3 vb = getTrackBallVector(currentX, currentY);

        //     float angle = acos(std::min(1.0f, glm::dot(va,vb)));
        //     glm::vec3 axis_in_camera_coord = glm::cross(va, vb);
        //     glm::mat3 camera2object = glm::inverse(glm::mat3(viewT*modelT));
        //     glm::vec3 axis_in_object_coord = camera2object * axis_in_camera_coord;
        //     modelT = glm::rotate(modelT, angle, axis_in_object_coord);
        //     glUniformMatrix4fv(vModel_uniform, 1, GL_FALSE, glm::value_ptr(modelT));

        //     oldX = currentX;
        //     oldY = currentY;
        // }

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
        glUniform3f(light_pos_value, 1000, 100.0, 0.0);
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
int total_phi_steps = 61;
int total_theta_steps = 46;
float Radius = 30;
float X(float phi, float theta)
{
    return sin(phi) * cos(theta);
}
float Y(float phi, float theta)
{
    return sin(phi) * sin(theta);   
}
float Z(float phi, float theta)
{    
    return cos(phi);
}
const int n = 101;
double mat[n][n];
void sphere_parametric_equation(float phi, float theta, float *coordinates)
{
    coordinates[0] = Radius * X(phi, theta);
    coordinates[1] = Radius * Y(phi, theta);
    coordinates[2] = Radius * Z(phi, theta);
}
void sphere_parametric_equation_2(float phi, float theta, float *coordinates)
{
    float u = phi/PI;
    float v = theta/(2 * PI);
    // big = max(big, v);
    // small = min(small, v);
    u*=101;
    v*=101;
    int ii = int(u);
    int jj = int(v);
    // cout<<"ii = "<<ii<<"\n";
    // cout<<"jj = "<<jj<<"\n";
    coordinates[0] = (Radius + mat[ii][jj]) * X(phi, theta);
    coordinates[1] = (Radius + mat[ii][jj]) * Y(phi, theta);
    coordinates[2] = (Radius + mat[ii][jj]) * Z(phi, theta);
}
float get_phi_angle(int phi_step)
{
    return phi_step*(PI)/(total_phi_steps -1);
}
float get_theta_angle(int theta_step)
{
    return theta_step*(2*PI)/(total_theta_steps);
}
bool valid(int i,int j,int n)
{
    return 0<=i && i<n && 0<=j && j<n;
}
void smooth(double m[][101], int n)
{
    double temp[n][n];
    int k = 3;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            double den = 0 , num = 0;
            for(int x=-k;x<=k;x++)
            {
                for(int y=-k;y<=k;y++)
                {
                    double val = 0;
                    int ti = i + x, tj = j + y;
                    if(valid(ti,tj,n))
                    {
                        double w = (k * k - abs(x) - abs(y));
                        val = m[ti][tj] * w;
                        num+=val;
                        den += w;
                    }
                }
            }
            temp[i][j] = num/den;
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            m[i][j] = temp[i][j];
        }
    }
}
void createCubeObject(unsigned int &program, unsigned int &cube_VAO)
{
    glUseProgram(program);

    //Bind shader variables
    int vVertex_attrib = glGetAttribLocation(program, "vVertex");
    if(vVertex_attrib == -1) {
        fprintf(stderr, "Could not bind location: vVertex\n");
        exit(0);
    }

    //Cube data
    // GLfloat cube_vertices[] = {10, 10, -10, -10, 10, -10, -10, -10, -10, 10, -10, -10, //Front
    //                10, 10, 10, -10, 10, 10, -10, -10, 10, 10, -10, 10}; //Back
    // GLushort cube_indices[] = {
    //             0, 1, 2, 0, 2, 3, //Front
    //             4, 7, 5, 5, 7, 6, //Back
    //             1, 6, 2, 1, 5, 6, //Left
    //             0, 3, 4, 4, 7, 3, //Right
    //             0, 4, 1, 4, 5, 1, //Top
    //             2, 6, 3, 3, 6, 7 //Bottom

    //             };













    //Generate VAO object
    glGenVertexArrays(1, &cube_VAO);
    glBindVertexArray(cube_VAO);

    //Create VBOs for the VAO
    //Position information (data + format)
    int nVertices = 500 * 500 * 2 * 3; //(6 faces) * (2 triangles each) * (3 vertices each)
    GLfloat *expanded_vertices = new GLfloat[nVertices*3];
    // for(int i=0; i<nVertices; i++) {
    //     expanded_vertices[i*3] = cube_vertices[cube_indices[i]*3];
    //     expanded_vertices[i*3 + 1] = cube_vertices[cube_indices[i]*3+1];
    //     expanded_vertices[i*3 + 2] = cube_vertices[cube_indices[i]*3+2];
    // }

    // int index = 0;


    int x_offset = 0;
    int index = 0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            mat[i][j] = 1;
        }
    }
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1;j++)
        {
            expanded_vertices[index++] = (j) - n/2 + x_offset; 
            expanded_vertices[index++] = mat[i + 1][j]; 
            expanded_vertices[index++] = (i + 1) - n/2; 

            expanded_vertices[index++] = (j + 1) - n/2 + x_offset; 
            expanded_vertices[index++] = mat[i + 1][j + 1]; 
            expanded_vertices[index++] = (i + 1) - n/2; 

            expanded_vertices[index++] = (j + 1) - n/2 + x_offset; 
            expanded_vertices[index++] = mat[i][j + 1]; 
            expanded_vertices[index++] = (i) - n/2; 


            expanded_vertices[index++] = (j) - n/2 + x_offset; 
            expanded_vertices[index++] = mat[i + 1][j]; 
            expanded_vertices[index++] = (i + 1) - n/2; 

            expanded_vertices[index++] = (j + 1) - n/2 + x_offset; 
            expanded_vertices[index++] = mat[i][j + 1]; 
            expanded_vertices[index++] = (i) - n/2; 

            expanded_vertices[index++] = (j) - n/2 + x_offset; 
            expanded_vertices[index++] = mat[i][j]; 
            expanded_vertices[index++] = (i) - n/2; 

        }
    }

    for(int i=10;i<n-10;i+=20)
    {
        for(int j=10;j<n-10;j+=20)
        {
            mat[i][j] = 300;
        }
    }
    smooth(mat,n);
    // for(int i=0;i<n;i++)
    // {
    //     for(int j=0;j<n;j++)
    //     {
    //         cout<<mat[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    x_offset+=1000;
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1;j++)
        {
            expanded_vertices[index++] = (j) - n/2 + x_offset; 
            expanded_vertices[index++] = mat[i + 1][j]; 
            expanded_vertices[index++] = (i + 1) - n/2; 

            expanded_vertices[index++] = (j + 1) - n/2 + x_offset; 
            expanded_vertices[index++] = mat[i + 1][j + 1]; 
            expanded_vertices[index++] = (i + 1) - n/2; 

            expanded_vertices[index++] = (j + 1) - n/2 + x_offset; 
            expanded_vertices[index++] = mat[i][j + 1]; 
            expanded_vertices[index++] = (i) - n/2; 


            expanded_vertices[index++] = (j) - n/2 + x_offset; 
            expanded_vertices[index++] = mat[i + 1][j]; 
            expanded_vertices[index++] = (i + 1) - n/2; 

            expanded_vertices[index++] = (j + 1) - n/2 + x_offset; 
            expanded_vertices[index++] = mat[i][j + 1]; 
            expanded_vertices[index++] = (i) - n/2; 

            expanded_vertices[index++] = (j) - n/2 + x_offset; 
            expanded_vertices[index++] = mat[i][j]; 
            expanded_vertices[index++] = (i) - n/2; 

        }
    }


    float coordinates[3];
    x_offset+=1000;


    for(int phi_step = 0;phi_step<total_phi_steps;phi_step++)
    {
        if(0==phi_step || (total_phi_steps-1)==phi_step) continue;

        if(1==phi_step)
        {
            for(int theta_step = 0;theta_step<total_theta_steps;theta_step++)
            {
                
                sphere_parametric_equation(get_phi_angle(phi_step - 1),get_theta_angle((0)%total_theta_steps),coordinates);
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];

                sphere_parametric_equation(get_phi_angle(phi_step),get_theta_angle((theta_step + 1)%total_theta_steps),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];

                sphere_parametric_equation(get_phi_angle(phi_step),get_theta_angle(theta_step),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];
            }   
        }
        else if((total_phi_steps - 2)==phi_step)
        {
            for(int theta_step = 0;theta_step<total_theta_steps;theta_step++)
            {
                sphere_parametric_equation(get_phi_angle(phi_step + 1),get_theta_angle(0),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];

                sphere_parametric_equation(get_phi_angle(phi_step),get_theta_angle(theta_step),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];

                sphere_parametric_equation(get_phi_angle(phi_step),get_theta_angle((theta_step + 1)%total_theta_steps),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];
            } 
        }

        if(1 < phi_step)
        {
            for(int theta_step = 0; theta_step<total_theta_steps;theta_step++)
            {
                sphere_parametric_equation(get_phi_angle(phi_step - 1),get_theta_angle(theta_step),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];

                sphere_parametric_equation(get_phi_angle(phi_step),get_theta_angle(theta_step),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];

                sphere_parametric_equation(get_phi_angle(phi_step),get_theta_angle((theta_step + 1)%total_theta_steps),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];




                sphere_parametric_equation(get_phi_angle(phi_step - 1),get_theta_angle(theta_step),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];

                sphere_parametric_equation(get_phi_angle(phi_step),get_theta_angle((theta_step + 1)%total_theta_steps),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];

                sphere_parametric_equation(get_phi_angle(phi_step - 1),get_theta_angle((theta_step + 1)%total_theta_steps),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];
            }
        }
    }


    x_offset+=1000;


    for(int phi_step = 0;phi_step<total_phi_steps;phi_step++)
    {
        if(0==phi_step || (total_phi_steps-1)==phi_step) continue;

        if(1==phi_step)
        {
            for(int theta_step = 0;theta_step<total_theta_steps;theta_step++)
            {
                sphere_parametric_equation_2(get_phi_angle(phi_step - 1),get_theta_angle((0)%total_theta_steps),coordinates);
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];


                sphere_parametric_equation_2(get_phi_angle(phi_step),get_theta_angle((theta_step + 1)%total_theta_steps),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];

                sphere_parametric_equation_2(get_phi_angle(phi_step),get_theta_angle(theta_step),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];
            }   
        }
        else if((total_phi_steps - 2)==phi_step)
        {
            for(int theta_step = 0;theta_step<total_theta_steps;theta_step++)
            {
                sphere_parametric_equation_2(get_phi_angle(phi_step + 1),get_theta_angle(0),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];

                sphere_parametric_equation_2(get_phi_angle(phi_step),get_theta_angle(theta_step),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];

                sphere_parametric_equation_2(get_phi_angle(phi_step),get_theta_angle((theta_step + 1)%total_theta_steps),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];
            } 
        }

        if(1 < phi_step)
        {
            for(int theta_step = 0; theta_step<total_theta_steps;theta_step++)
            {
                sphere_parametric_equation_2(get_phi_angle(phi_step - 1),get_theta_angle(theta_step),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];

                sphere_parametric_equation_2(get_phi_angle(phi_step),get_theta_angle(theta_step),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];

                sphere_parametric_equation_2(get_phi_angle(phi_step),get_theta_angle((theta_step + 1)%total_theta_steps),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];




                sphere_parametric_equation_2(get_phi_angle(phi_step - 1),get_theta_angle(theta_step),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];

                sphere_parametric_equation_2(get_phi_angle(phi_step),get_theta_angle((theta_step + 1)%total_theta_steps),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];

                sphere_parametric_equation_2(get_phi_angle(phi_step - 1),get_theta_angle((theta_step + 1)%total_theta_steps),coordinates);
                // for(int i=0;i<3;i++) expanded_vertices[index++] = coordinates[i];
                expanded_vertices[index++] = coordinates[0] + x_offset;
                expanded_vertices[index++] = coordinates[1];
                expanded_vertices[index++] = coordinates[2];
            }
        }
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

