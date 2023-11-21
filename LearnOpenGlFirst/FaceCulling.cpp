/*
面剔除 节省性能
https://learnopengl-cn.github.io/04%20Advanced%20OpenGL/04%20Face%20culling/

只绘制面向观察者的面
OpenGL能够检查所有面向Front Facing 观察者的面 并且渲染他们 而丢弃那些背向Back Facing的面，节省我们很多的
片段着色器调用  使用方法 分析顶点数据的环绕顺序 winding order

环绕顺序
定义一个三角形顶点时 我们会以特定的环绕顺序来定义它们 可能是顺时针Clockwise 也可能是逆时针 Counter-closewise
每个三角形由3个顶点所组成
float vertices[] = {
// 顺时针
vertices[0], // 顶点1
vertices[1], // 顶点2
vertices[2], // 顶点3
// 逆时针
vertices[0], // 顶点1
vertices[2], // 顶点3
vertices[1]  // 顶点2
};
OpenGL 在渲染图元的时候使用环绕顺序来决定一个三角形是一个正向三角形还是逆向三角形  逆时针三角形被处理为正向三角形
环绕顺序是在光栅化阶段进行的 也就是顶点着色器之后


*/