# Nora-Shade
An OpenGL shader combiner

Usage: NoraShade.exe <source-directory> <shader-name>

Example: NoraShade rawshaders/shader_example shader_example

Note: Source directory is relative to the location of NoraShade itself, and will create the .shader file within the same directory as NoraShade.

Make sure that the source directory has a vertex.txt, fragment.txt, and attributes.txt

Optionally, if using a geometry shader, make sure that it is included in the directory as geometry.txt

The .Shader file format is as follows

File = {
  Header = {
    char[4] verification string = "SHDR"
    uint attribute data size
    uint vertex data size
    uint fragment data size
    uint geometry data size
  }
  char[attribute data size] attributes
  char[vertex data size] vertex shader
  char[fragment data size] fragment shader
  char[geometry data size] geometry shader
}

Note that the attributes in the attributes.txt should always be in the same order as they are defined within the OpenGL application, so if the "vertexPosition" attribute is supposed to be set to attribute index 0, then it should be on the first line of attributes.txt
