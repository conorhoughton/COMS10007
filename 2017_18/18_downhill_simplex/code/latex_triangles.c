//latex_triangles.c
//related to 13_downhill_simplex part of the
//PandA1 course at UoBristol
//2015 Conor Houghton conor.houghton@bristol.ac.uk

//To the extent possible under law, the author has dedicated all copyright 
//and related and neighboring rights to this software to the public domain 
//worldwide. This software is distributed without any warranty. 

#include<stdio.h>


void make_preamble(FILE *output_file)
{
  fputs("\\documentclass[11pt,a4paper]{scrartcl}\n",output_file);
  fputs("\\typearea{12}\n",output_file);
  fputs("\\usepackage{tikz}\n",output_file);
  fputs("\\usetikzlibrary{calc,positioning}\n",output_file);
  fputs("\\usetikzlibrary{shapes,arrows}\n",output_file);
  fputs("\\begin{document}\n",output_file);

}


void make_postamble(FILE *output_file)
{
  fputs("\\end{document}\n",output_file);
}

void add_title(FILE *output_file, char* title)
{
  fprintf(output_file,"\\section*{%s}\n",title);
}

void open_triangle(FILE *output_file)
{  
  fputs("\\begin{tikzpicture}\n",output_file);
}

void append_triangle(FILE * output_file,double x[2],double y[2],double z[2],double scale)
{

  fprintf(output_file,"\\coordinate (x) at (%f,%f);\n",x[0]/scale,x[1]/scale);
  fprintf(output_file,"\\coordinate (y) at (%f,%f);\n",y[0]/scale,y[1]/scale);
  fprintf(output_file,"\\coordinate (z) at (%f,%f);\n",z[0]/scale,z[1]/scale);
  fprintf(output_file,"\\draw (x) -- (y);\n");
  fprintf(output_file,"\\draw (y) -- (z);\n");
  fprintf(output_file,"\\draw (z) -- (x);\n");

}

void close_triangle(FILE *output_file)
{
 fprintf(output_file,"\\end{tikzpicture}\n");
}

void add_triangle(FILE *output_file,double x[2],double y[2],double z[2])
{
  fputs("\\begin{tikzpicture}\n",output_file);
  fprintf(output_file,"\\coordinate (x) at (%f,%f);\n",x[0],x[1]);
  fprintf(output_file,"\\coordinate (y) at (%f,%f);\n",y[0],y[1]);
  fprintf(output_file,"\\coordinate (z) at (%f,%f);\n",z[0],z[1]);
  fprintf(output_file,"\\draw (x) -- (y);\n");
  fprintf(output_file,"\\draw (y) -- (z);\n");
  fprintf(output_file,"\\draw (z) -- (x);\n");
  fprintf(output_file,"\\end{tikzpicture}\n");

}


void add_centered_triangle(FILE *output_file,double x[2],double y[2],double z[2])
{
  int i;
  double c;

  double x_c[2],y_c[2],z_c[2];


  for(i=0;i<2;i++)
    {
      c=(x[i]+y[i]+z[i])/3.0;
      x_c[i]=x[i]-c;
      y_c[i]=y[i]-c;
      z_c[i]=z[i]-c;
    }

  add_triangle(output_file,x,y,z);

}

/*
int main()
{
  

  FILE * output_file;
  output_file=fopen("triangles.tex","w");

  make_preamble(output_file);

  double x[2]={0,1};
  double y[2]={1,2};
  double z[2]={-1,-1};

  add_centered_triangle(output_file,x,y,z);

  make_postamble(output_file);

  fclose(output_file);
}
*/
