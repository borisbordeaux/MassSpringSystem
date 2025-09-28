#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_internal.h"

#include <iostream>
#include <random>
#include "massspringsystem/massspringsystem.h"
#include "implot/implot.h"
#include "imguifiledialog/ImGuiFileDialog.h"
#include <armadillo>

void initSystem(mss::MassSpringSystem& system, std::vector<float>& subdivisionPointsX, std::vector<float>& subdivisionPointsY, std::vector<float>& springsX, std::vector<float>& springsY, arma::mat& controlPoints) {
    subdivisionPointsX.resize(system.masses().size());
    subdivisionPointsY.resize(system.masses().size());
    springsX.resize(system.springs().size() * 2);
    springsY.resize(system.springs().size() * 2);
    if (controlPoints.n_cols != system.dimension()) {
        controlPoints.clear();
        controlPoints.set_size(2, system.dimension()); // always 2D
        float pi = 3.1415926f;
        float r = 500.0f;
        std::size_t n = system.dimension();
        for (int i = 0; i < n; i++) {
            float angle = static_cast<float>(i) * 2.0f * pi / static_cast<float>(n);
            controlPoints(0, i) = r * std::cos(angle);
            controlPoints(1, i) = r * std::sin(angle);
        }
    }
}

void loadInitSystem(mss::MassSpringSystem& system, float k, float l, float damping, std::vector<float>& subdivisionPointsX, std::vector<float>& subdivisionPointsY, std::vector<float>& springsX, std::vector<float>& springsY, arma::mat& controlPoints) {
    system.clear(9);
    controlPoints.set_size(2, 9);
    controlPoints << 600.0 << 300.0 << 0.0 << -300.0 << -600.0 << -338.0 << -300.0 << 300.0 << 338.0 << arma::endr
                  << 0.0 << 520.0 << 390.0 << 520.0 << 0.0 << -195.0 << -520.0 << -520.0 << -195.0 << arma::endr;
    // add fixed masses for control points
    system.addMass(mss::Vector { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
    system.addMass(mss::Vector { 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
    system.addMass(mss::Vector { 0.0f, 0.25f, 0.50f, 0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
    system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
    system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f });
    system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.0f, 0.25f, 0.50f, 0.25f, 0.0f, 0.0f });
    system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f });
    system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f });
    system.addMass(mss::Vector { 0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.25f, 0.50f });

    // add subdivision points
    for (int i = 0; i < 33; i++) {
        if (i == 9 - 9) {
            system.addMass(mss::Vector { 0.6666f, 0.3333f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
        } else if (i == 16 - 9) {
            system.addMass(mss::Vector { 0.3333f, 0.6666f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
        } else if (i == 22 - 9) {
            system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.6666f, 0.3333f, 0.0f, 0.0f, 0.0f, 0.0f });
        } else if (i == 28 - 9) {
            system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.3333f, 0.6666f, 0.0f, 0.0f, 0.0f, 0.0f });
        } else if (i == 33 - 9) {
            system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.6666f, 0.3333f, 0.0f });
        } else if (i == 39 - 9) {
            system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.3333f, 0.6666f, 0.0f });
        } else if (i == 15 - 9) {
            system.addMass(mss::Vector { 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f });
        } else if (i == 40 - 9) {
            system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f });
        } else if (i == 17 - 9) {
            system.addMass(mss::Vector { 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
        } else if (i == 21 - 9) {
            system.addMass(mss::Vector { 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
        } else if (i == 29 - 9) {
            system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f });
        } else if (i == 32 - 9) {
            system.addMass(mss::Vector { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f });
        } else {
            system.addMass(damping);
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

    initSystem(system, subdivisionPointsX, subdivisionPointsY, springsX, springsY, controlPoints);
}

void alignPoints(mss::MassSpringSystem& system) {
    std::vector<std::size_t> points = {
            10, 11, 20,
            23, 24, 27,
            34, 35, 38,
            13, 12, 19,
            19, 18, 26,
            26, 25, 31,
            31, 30, 37,
            37, 36, 41,
            41, 14, 13
    };
    for (std::size_t i = 0; i < points.size(); i += 3) {
        auto& pL = system.masses().at(points[i]);
        auto& pM = system.masses().at(points[i + 1]);
        auto& pR = system.masses().at(points[i + 2]);
        for (std::size_t dim = 0; dim < system.dimension(); dim++) {
            pM.position().at(dim) = (pL.position().at(dim) + pR.position().at(dim)) / 2.0f;
        }
    }
}

void updateK(mss::MassSpringSystem& system, float newK) {
    std::vector<std::size_t> springs = { 25, 26, 27, 28, 30, 31, 36, 37, 39, 40, 45, 46 };
    for (std::size_t i: springs) {
        system.springs()[i].setK(newK);
    }
}

ImVec2 averageOf(std::vector<ImVec2> const& points) {
    ImVec2 res;
    for (ImVec2 const& point: points) {
        res.x += point.x;
        res.y += point.y;
    }
    res.x /= static_cast<float>(points.size());
    res.y /= static_cast<float>(points.size());
    return res;
}

void drawFace(std::vector<ImVec2> const& points, ImU32 col) {
    ImPlot::PushPlotClipRect();
    for (int i = 0; i < points.size() - 1; i++) {
        std::size_t nextIndex = i + 1 == points.size() - 1 ? 0 : i + 1;
        ImPlot::GetPlotDrawList()->AddTriangleFilled(points[i], points[nextIndex], points[points.size() - 1], col);
    }
    ImPlot::PopPlotClipRect();
}

ImVec2 modelingCoordFromBarycentricCoord(mss::Vector const& pos, arma::mat const& controlPoints) {
    float x = 0;
    float y = 0;
    for (std::size_t j = 0; j < pos.dim(); j++) {
        x += pos.at(j) * static_cast<float>(controlPoints.at(0, j));
        y += pos.at(j) * static_cast<float>(controlPoints.at(1, j));
    }
    return { x, y };
}

void drawSubFaces(std::vector<arma::mat99> const& T, arma::mat::fixed<2, 9> const& controlPoints, int iterationLevel, std::size_t indexColor, int maxIterationLevel) {
    std::vector<ImU32> faceColors = {
            ImColor(129, 50, 255),
            ImColor(252, 127, 0),
            ImColor(0, 71, 232),
            ImColor(205, 207, 0),
            ImColor(206, 0, 0),
            ImColor(0, 183, 0),
            ImColor(178, 180, 177)
    };
    if (iterationLevel == 0) {
        std::vector<ImVec2> points;
        points.reserve(9);
        for (int row = 0; row < 9; row++) {
            points.push_back(ImPlot::PlotToPixels(controlPoints.at(0, row), controlPoints.at(1, row)));
        }
        points.push_back(averageOf(points));
        drawFace(points, faceColors[indexColor]);
    } else {
        for (std::size_t i = 0; i < T.size(); i++) {
            if (iterationLevel == maxIterationLevel) {
                drawSubFaces(T, controlPoints * T[i], iterationLevel - 1, i, maxIterationLevel);
            } else {
                drawSubFaces(T, controlPoints * T[i], iterationLevel - 1, indexColor, maxIterationLevel);
            }
        }
    }
}

void drawIFS(mss::MassSpringSystem const& system, arma::mat::fixed<2, 9> const& controlPoints, int iterationLevel) {
    std::vector<std::vector<std::size_t>> indices = {
            { 0,  9,  10, 11, 12, 13, 14, 8,  15 },
            { 16, 1,  17, 2,  18, 19, 12, 11, 20 },
            { 18, 2,  21, 3,  22, 23, 24, 25, 26 },
            { 25, 24, 27, 28, 4,  29, 5,  30, 31 },
            { 35, 36, 37, 30, 5,  32, 6,  33, 34 },
            { 8,  14, 41, 36, 35, 38, 39, 7,  40 }
    };

    std::vector<arma::mat99> T;
    T.resize(6);
    for (int i = 0; i < 6; i++) {
        for (int col = 0; col < 9; col++) {
            for (int row = 0; row < 9; row++) {
                T[i].at(row, col) = system.masses().at(indices[i][col]).position().at(row);
            }
        }
    }

    drawSubFaces(T, controlPoints, iterationLevel, 6, iterationLevel);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SAMPLES, 16);

    // Create window with graphics context
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only
    GLFWwindow* window = glfwCreateWindow((int) (1280 * main_scale), (int) (800 * main_scale), "MassSpringSystem example", nullptr, nullptr);
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
    style.ScaleAllSizes(main_scale); // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
    style.AntiAliasedFill = false;               // Better result when multisampling is enabled
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
    char textDescription[5000] = { "# d dimension\n"
                                   "d 3\n"
                                   "# fixed masses with barycentric coordinates\n"
                                   "m 1.0 0.0 0.0\n"
                                   "m 0.0 1.0 0.0\n"
                                   "m 0.0 0.0 1.0\n"
                                   "# movable masses with random coordinates\n"
                                   "# n number_of_masses damping\n"
                                   "n 2 0.9\n"
                                   "# springs connecting two masses\n"
                                   "# s index_mass_1 index_mass_2 k length\n"
                                   "s 3 0 0.03 0.0\n"
                                   "s 3 1 0.03 0.0\n"
                                   "s 3 2 0.03 0.0\n"
                                   "s 4 0 0.01 0.0\n"
                                   "s 4 1 0.03 0.0" };
    float lacunaK = k;
    bool visibleIFS = true;
    int iterationLevel = 0;

    arma::mat controlPoints;

    // Will be computed on each frame
    std::vector<float> subdivisionPointsX;
    std::vector<float> subdivisionPointsY;
    std::vector<float> springsX;
    std::vector<float> springsY;

    mss::MassSpringSystem system(9);
    loadInitSystem(system, k, l, damping, subdivisionPointsX, subdivisionPointsY, springsX, springsY, controlPoints);

    // Resize them for performance purposes
    subdivisionPointsX.resize(system.masses().size());
    subdivisionPointsY.resize(system.masses().size());
    springsX.resize(system.springs().size() * 2);
    springsY.resize(system.springs().size() * 2);

    ImPlotStyle& imPlotStyle = ImPlot::GetStyle();
    ImVec4* colors = imPlotStyle.Colors;
    colors[ImPlotCol_Line] = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
    colors[ImPlotCol_PlotBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    imPlotStyle.LineWeight = 2.0f;

    // Main loop
    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Specify all ImGui widgets we want to render
        {
            ImGuiID dockSpaceId = ImGui::GetID("MyDockSpaceId");
            const bool init = ImGui::DockBuilderGetNode(dockSpaceId) == nullptr;

            if (init) {
                std::cout << dockSpaceId << std::endl;
                ImGui::DockBuilderAddNode(dockSpaceId, ImGuiDockNodeFlags_DockSpace);
                ImGui::DockBuilderSetNodeSize(dockSpaceId, ImGui::GetMainViewport()->Size);
                // Horizontal split : 70% for the main window and 30% for the description window
                ImGuiID dock_left, dock_right;
                dock_left = ImGui::DockBuilderSplitNode(dockSpaceId, ImGuiDir_Left, 0.7f, nullptr, &dock_right);
                // Associate windows to dock spaces
                ImGui::DockBuilderDockWindow("Mass Spring System", dock_left);
                ImGui::DockBuilderDockWindow("Text description", dock_right);
                ImGui::DockBuilderFinish(dockSpaceId);
            }
            ImGui::DockSpaceOverViewport(dockSpaceId, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_AutoHideTabBar);

            //ImGui::ShowDemoWindow();
            //ImPlot::ShowDemoWindow();
            ImGui::Begin("Mass Spring System");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

            if (ImGui::BeginTable("table1", 2)) {
                ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthStretch); // Default to 200.0f
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::AlignTextToFramePadding();
                ImGui::Text("Lacuna springs constant");
                ImGui::TableNextColumn();
                ImGui::SetNextItemWidth(-1);
                if (ImGui::SliderFloat("##Lacuna K", &lacunaK, 0.001f, 0.2f, "%.3f", ImGuiSliderFlags_AlwaysClamp)) {
                    updateMSS = true;
                    updateK(system, lacunaK);
                }
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::AlignTextToFramePadding();
                ImGui::Text("Spring Constant:");
                ImGui::TableNextColumn();
                ImGui::SetNextItemWidth(-1);
                ImGui::SliderFloat("##Spring Constant", &k, 0.001f, 0.5f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::AlignTextToFramePadding();
                ImGui::Text("  Spring Length:");
                ImGui::TableNextColumn();
                ImGui::SetNextItemWidth(-1);
                ImGui::SliderFloat("##Spring Length", &l, 0.0f, 1.0f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::AlignTextToFramePadding();
                ImGui::Text("        Damping:");
                ImGui::TableNextColumn();
                ImGui::SetNextItemWidth(-1);
                ImGui::SliderFloat("##Damping", &damping, 0.0f, 1.0f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
                ImGui::EndTable();
            }
            if (ImGui::Checkbox("Enable VSync", &enableVSync)) { glfwSwapInterval(enableVSync ? 1 : 0); }
            ImGui::SameLine();
            ImGui::Checkbox("Update Mass Spring System", &updateMSS);
            ImGui::Checkbox("Control Points", &visibleControlPoints);
            ImGui::SameLine();
            ImGui::Checkbox("Subdivision Points", &visibleSubdivisionPoints);
            ImGui::SameLine();
            ImGui::Checkbox("Springs", &visibleSprings);
            if (system.dimension() == 9 && system.masses().size() == 42) {
                ImGui::SameLine();
                ImGui::Checkbox("IFS", &visibleIFS);
                ImGui::SameLine();
                ImGui::SetNextItemWidth(200);
                ImGui::SliderInt("Iteration Level", &iterationLevel, 0, 7, "%d", ImGuiSliderFlags_AlwaysClamp);
            }
            if (ImGui::Button("Reset System")) {
                loadInitSystem(system, k, l, damping, subdivisionPointsX, subdivisionPointsY, springsX, springsY, controlPoints);
            }
            ImGui::SameLine();
            if (ImGui::Button("Load From File...")) {
                IGFD::FileDialogConfig config;
                config.path = "../../example";
                config.flags |= ImGuiFileDialogFlags_::ImGuiFileDialogFlags_Modal;
                ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose an MSS File", ".mss", config);
            }
            if (system.dimension() == 9 && system.masses().size() == 42 && ImGui::Button("Test Align")) {
                updateMSS = false;
                alignPoints(system);
            }

            if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey", ImGuiWindowFlags_NoCollapse, ImVec2(700, 350))) {
                if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
                    std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                    if (!system.loadFromFile(filePathName)) {
                        ImGui::OpenPopup("Error");
                    } else {
                        visibleIFS = false;
                        initSystem(system, subdivisionPointsX, subdivisionPointsY, springsX, springsY, controlPoints);
                    }
                }
                ImGuiFileDialog::Instance()->Close();
            }

            ImGui::Begin("Text description", nullptr, ImGuiWindowFlags_NoCollapse);
            if (ImGui::Button("Load", ImVec2(-1, 0))) {
                if (!system.loadFromString(textDescription)) {
                    ImGui::OpenPopup("Error");
                } else {
                    visibleIFS = false;
                    initSystem(system, subdivisionPointsX, subdivisionPointsY, springsX, springsY, controlPoints);
                }
            }

            ImGui::InputTextMultiline("##", &textDescription[0], 5000, ImVec2(-1, -1));
            if (ImGui::BeginPopupModal("Error", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
                ImGui::Text("Error: Invalid description!");
                ImGui::Separator();

                if (ImGui::BeginTable("table2", 3, ImGuiTableFlags_SizingStretchSame)) {
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    ImGui::TableNextColumn();
                    if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
                    ImGui::EndTable();
                }

                ImGui::SetItemDefaultFocus();
                ImGui::EndPopup();
            }
            ImGui::End();

            if (ImGui::BeginPopupModal("Error", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
                ImGui::Text("Error: Invalid description!");
                ImGui::Separator();

                if (ImGui::BeginTable("table2", 3, ImGuiTableFlags_SizingStretchSame)) {
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    ImGui::TableNextColumn();
                    if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
                    ImGui::EndTable();
                }

                ImGui::SetItemDefaultFocus();
                ImGui::EndPopup();
            }

            // compute coordinates based on barycentric coordinates
            for (int i = 0; i < system.masses().size(); i++) {
                ImVec2 pos = modelingCoordFromBarycentricCoord(system.masses()[i].position(), controlPoints);
                subdivisionPointsX[i] = pos.x;
                subdivisionPointsY[i] = pos.y;
            }

            // compute X/Y coordinates of spring lines
            for (std::size_t i = 0; i < system.springs().size(); i++) {
                ImVec2 pos1 = modelingCoordFromBarycentricCoord(system.springs()[i].m1().position(), controlPoints);
                ImVec2 pos2 = modelingCoordFromBarycentricCoord(system.springs()[i].m2().position(), controlPoints);
                springsX[2 * i] = pos1.x;
                springsX[2 * i + 1] = pos2.x;
                springsY[2 * i] = pos1.y;
                springsY[2 * i + 1] = pos2.y;
            }

            if (ImPlot::BeginPlot("Mass Spring System Viewer", ImVec2(-1, -1), ImPlotFlags_Equal | ImPlotFlags_NoLegend | ImPlotFlags_NoMouseText)) {
                ImPlot::SetupAxes("##x", "##y",
                                  ImPlotAxisFlags_NoGridLines | ImPlotAxisFlags_NoTickMarks | ImPlotAxisFlags_NoTickLabels,
                                  ImPlotAxisFlags_NoGridLines | ImPlotAxisFlags_NoTickMarks | ImPlotAxisFlags_NoTickLabels);

                if (visibleIFS) {
                    drawIFS(system, controlPoints, iterationLevel);
                }
                if (visibleSubdivisionPoints) {
                    ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 4, ImColor(0, 0, 0, 127), IMPLOT_AUTO);
                    ImPlot::PlotScatter("Data 2", subdivisionPointsX.data(), subdivisionPointsY.data(), static_cast<int>(system.masses().size()));
                }
                if (visibleSprings) {
                    ImPlot::PlotLine("Springs", springsX.data(), springsY.data(), static_cast<int>(system.springs().size() * 2), ImPlotLineFlags_Segments);
                }
                if (visibleControlPoints) {
                    for (std::size_t i = 0; i < system.dimension(); i++) {
                        ImPlot::DragPoint(static_cast<int>(i), &controlPoints.at(0, i), &controlPoints.at(1, i), ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
                    }
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