#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>
#include <random>
#include "massspringsystem/massspringsystem.h"
#include "implot/implot.h"

void initSystem(mss::MassSpringSystem& system, float k, float l, float damping) {
    system.clear();
    system.setDamping(damping);
    //add fixed control points
    system.addMass(mss::Vector { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }, true);
    system.addMass(mss::Vector { 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }, true);
    system.addMass(mss::Vector { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }, true);
    system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }, true);
    system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f }, true);
    system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f }, true);
    system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f }, true);
    system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f }, true);
    system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f }, true);

    //add subdivision points
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> distribution(0.0f, 0.25f);
    for (int i = 0; i < 33; i++) {
        if (i == 9 - 9) {
            system.addMass(mss::Vector { 0.6666f, 0.3333f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }, true);
        } else if (i == 16 - 9) {
            system.addMass(mss::Vector { 0.3333f, 0.6666f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }, true);
        } else if (i == 22 - 9) {
            system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.6666f, 0.3333f, 0.0f, 0.0f, 0.0f, 0.0f }, true);
        } else if (i == 28 - 9) {
            system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.3333f, 0.6666f, 0.0f, 0.0f, 0.0f, 0.0f }, true);
        } else if (i == 33 - 9) {
            system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.6666f, 0.3333f, 0.0f }, true);
        } else if (i == 39 - 9) {
            system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.3333f, 0.6666f, 0.0f }, true);
        } else if (i == 15 - 9) {
            system.addMass(mss::Vector { 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f }, true);
        } else if (i == 40 - 9) {
            system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f }, true);
        } else if (i == 17 - 9) {
            system.addMass(mss::Vector { 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }, true);
        } else if (i == 21 - 9) {
            system.addMass(mss::Vector { 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }, true);
        } else if (i == 29 - 9) {
            system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f }, true);
        } else if (i == 32 - 9) {
            system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f }, true);
        } else {
            float n1 = distribution(generator);
            float n2 = distribution(generator);
            float n3 = distribution(generator);
            float n4 = distribution(generator);
            float n5 = distribution(generator);
            float n6 = distribution(generator);
            float n7 = distribution(generator);
            float n8 = distribution(generator);
            float n9 = 1.0f - n1 - n2 - n3 - n4 - n5 - n6 - n7 - n8;
            system.addMass(mss::Vector { n1, n2, n3, n4, n5, n6, n7, n8, n9 });
        }
    }

    system.addSpring(0, 9, k, l);
    system.addSpring(0, 15, k, l);
    system.addSpring(1, 16, k, l);
    system.addSpring(1, 17, k, l);
    system.addSpring(2, 17, k, l);
    system.addSpring(2, 18, k, l);
    system.addSpring(2, 21, k, l);
    system.addSpring(3, 21, k, l);
    system.addSpring(3, 22, k, l);
    system.addSpring(4, 28, k, l);
    system.addSpring(4, 29, k, l);
    system.addSpring(5, 29, k, l);
    system.addSpring(5, 30, k, l);
    system.addSpring(5, 32, k, l);
    system.addSpring(6, 32, k, l);
    system.addSpring(6, 33, k, l);
    system.addSpring(7, 39, k, l);
    system.addSpring(7, 40, k, l);
    system.addSpring(8, 14, k, l);
    system.addSpring(8, 15, k, l);
    system.addSpring(8, 40, k, l);
    system.addSpring(9, 10, k, l);
    system.addSpring(10, 11, k, l);
    system.addSpring(11, 12, k, l);
    system.addSpring(11, 20, k, l);
    system.addSpring(12, 13, k, l);
    system.addSpring(12, 19, k, l);
    system.addSpring(13, 14, k, l);
    system.addSpring(14, 41, k, l);
    system.addSpring(16, 20, k, l);
    system.addSpring(18, 19, k, l);
    system.addSpring(18, 26, k, l);
    system.addSpring(22, 23, k, l);
    system.addSpring(23, 24, k, l);
    system.addSpring(24, 25, k, l);
    system.addSpring(24, 27, k, l);
    system.addSpring(25, 26, k, l);
    system.addSpring(25, 31, k, l);
    system.addSpring(27, 28, k, l);
    system.addSpring(30, 31, k, l);
    system.addSpring(30, 37, k, l);
    system.addSpring(33, 34, k, l);
    system.addSpring(34, 35, k, l);
    system.addSpring(35, 36, k, l);
    system.addSpring(35, 38, k, l);
    system.addSpring(36, 37, k, l);
    system.addSpring(36, 41, k, l);
    system.addSpring(38, 39, k, l);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Create window with graphics context
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only
    GLFWwindow* window = glfwCreateWindow((int) (1280 * main_scale), (int) (800 * main_scale), "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);  // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
    io.ConfigDpiScaleFonts = true;               // [Experimental] Automatically overwrite style.FontScaleDpi in Begin() when Monitor DPI changes. This will scale fonts but _NOT_ scale sizes/padding for now.
    io.ConfigDpiScaleViewports = true;           // [Experimental] Scale Dear ImGui and Platform Windows when Monitor DPI changes.

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state
    bool updateMSS = false;
    bool enableVSync = true;
    bool visibleControlPoints = true;
    bool visibleSubdivisionPoints = true;
    bool visibleSprings = true;
    float k = 0.01f;
    float l = 0.05f;
    float damping = 0.9f;

    std::vector<float> controlPointsX = { 600.0f, 300.0f, 0.0f, -300.0f, -600.0f, -324.0f, -300.0f, 300.0f, 324.0f };
    std::vector<float> controlPointsY = { 0.0f, 520.0f, 390.0f, 520.0f, 0.0f, -187.0f, -520.0f, -520.0f, -187.0f };

    // Will be computed on each frame
    std::vector<float> subdivisionPointsX;
    std::vector<float> subdivisionPointsY;
    subdivisionPointsX.resize(33);
    subdivisionPointsY.resize(33);

    mss::MassSpringSystem system(9, damping);
    initSystem(system, k, l, damping);

    // Will be computed on each frame
    std::vector<float> springsX;
    std::vector<float> springsY;
    springsX.resize(system.springs().size() * 2);
    springsY.resize(system.springs().size() * 2);


    ImPlotStyle& imPlotStyle = ImPlot::GetStyle();
    ImVec4* colors = imPlotStyle.Colors;
    colors[ImPlotCol_Line] = ImVec4(0.2f, 0.3f, 1.0f, 1.0f);
    colors[ImPlotCol_PlotBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    imPlotStyle.MajorTickLen = ImVec2(0, 0);
    imPlotStyle.MinorTickLen = ImVec2(0, 0);
    imPlotStyle.MajorTickSize = ImVec2(0, 0);
    imPlotStyle.MinorTickSize = ImVec2(0, 0);
    imPlotStyle.MajorGridSize = ImVec2(0, 0);
    imPlotStyle.MinorGridSize = ImVec2(0, 0);

    // Main loop
    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Specify all ImGui widgets we want to render
        {
            ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_AutoHideTabBar);

            ImGui::Begin("Mass Spring System");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::SliderFloat("Spring Constant", &k, 0.001f, 0.5f);
            ImGui::SliderFloat("Spring Length", &l, 0.0f, 1.0f);
            ImGui::SliderFloat("Damping", &damping, 0.0f, 1.0f);
            if (ImGui::Checkbox("Enable VSync", &enableVSync)) {
                glfwSwapInterval(enableVSync ? 1 : 0); // Enable vsync
            }
            ImGui::SameLine();
            ImGui::Checkbox("Update Mass Spring System", &updateMSS);
            ImGui::SameLine();
            ImGui::Checkbox("Visible Control Points", &visibleControlPoints);
            ImGui::SameLine();
            ImGui::Checkbox("Visible Subdivision Points", &visibleSubdivisionPoints);
            ImGui::SameLine();
            ImGui::Checkbox("Visible Springs", &visibleSprings);
            if (ImGui::Button("Reset System")) {
                initSystem(system, k, l, damping);
            }

            // compute coordinates based on barycentric coordinates
            for (int i = 9; i < 42; i++) {
                float x = 0;
                float y = 0;
                for (int j = 0; j < 9; j++) {
                    x += system.masses()[i].position().at(j) * controlPointsX[j];
                    y += system.masses()[i].position().at(j) * controlPointsY[j];
                }
                subdivisionPointsX[i - 9] = x;
                subdivisionPointsY[i - 9] = y;
            }

            // compute X/Y coordinates of spring lines
            for (std::size_t i = 0; i < system.springs().size(); i++) {
                float x1 = 0.0f;
                float x2 = 0.0f;
                float y1 = 0.0f;
                float y2 = 0.0f;

                mss::Vector m1Pos = system.springs()[i].m1().position();
                mss::Vector m2Pos = system.springs()[i].m2().position();

                for (int j = 0; j < 9; j++) {
                    x1 += m1Pos.at(j) * controlPointsX[j];
                    y1 += m1Pos.at(j) * controlPointsY[j];

                    x2 += m2Pos.at(j) * controlPointsX[j];
                    y2 += m2Pos.at(j) * controlPointsY[j];
                }

                springsX[2 * i] = x1;
                springsX[2 * i + 1] = x2;
                springsY[2 * i] = y1;
                springsY[2 * i + 1] = y2;
            }

            if (ImPlot::BeginPlot("Mass Spring System Viewer", ImVec2(-1, -1), ImPlotFlags_Equal | ImPlotFlags_NoLegend | ImPlotFlags_NoMouseText)) {
                ImPlot::SetupAxes("##x", "##y", ImPlotAxisFlags_NoGridLines | ImPlotAxisFlags_NoTickMarks | ImPlotAxisFlags_NoTickLabels, ImPlotAxisFlags_NoGridLines | ImPlotAxisFlags_NoTickMarks | ImPlotAxisFlags_NoTickLabels);
                if (visibleControlPoints) {
                    ImPlot::PlotScatter("Data 1", controlPointsX.data(), controlPointsY.data(), 9);
                }
                if (visibleSubdivisionPoints) {
                    ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
                    ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 4, ImPlot::GetColormapColor(1), IMPLOT_AUTO, ImPlot::GetColormapColor(1));
                    ImPlot::PlotScatter("Data 2", subdivisionPointsX.data(), subdivisionPointsY.data(), 33);
                    ImPlot::PopStyleVar();
                }
                if (visibleSprings) {
                    ImPlot::PlotLine("Springs", springsX.data(), springsY.data(), static_cast<int>(springsY.size()), ImPlotLineFlags_Segments);
                }
                ImPlot::EndPlot();
            }

            ImGui::End();

            if (updateMSS) {
                system.update();
            }
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
