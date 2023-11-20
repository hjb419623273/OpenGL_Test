﻿/*
理解颜色缓冲区

混合blending
OpenGL中 混合blending 通常是实现物体透明度Transparency的一种技术。透明就是说一个物体或者其中的一部分不是纯色Solid Color
它的颜色是物体本身和它背后其它物体的颜色的不同强度结合。一个有色玻璃窗是一个透明的物体，玻璃有它自己的颜色但还包含玻璃之后
所有物体的颜色

一个物体的透明度是通过它颜色的alpha的值来决定的 Alpha的颜色值是颜色向量的第四个分量 
std_image在纹理有alpha通道的时候会自动加载，仍要在纹理生成过程中告诉opengl 

GLSL提供discard命令 一旦被调用 它会保证片段不会被进一步处理 所以就不会进入 颜色缓冲

注意，当采样纹理的边缘的时候，OpenGL会对边缘的值和纹理下一个重复的值进行插值（因为我们将它的环绕方式设置为了GL_REPEAT。这通常是没问题的，但是由于我们使用了透明值，纹理图像的顶部将会与底部边缘的纯色值进行插值。这样的结果是一个半透明的有色边框，你可能会看见它环绕着你的纹理四边形。要想避免这个，每当你alpha纹理的时候，请将纹理的环绕方式设置为GL_CLAMP_TO_EDGE：

glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


混合
直接丢弃片段很好 但它不能让我们渲染半透明的图像 我们要么完全丢弃它 想要渲染有多个透明度级别的图像 我们需要启用混合 blending

*/