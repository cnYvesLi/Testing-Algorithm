#include<iostream>
#include<cmath>
#include<stdlib.h>
const int n = 100, k = 100, range = 1e8;
const double lr = 0.4, w = 0.6, c1 = 1.5, c2 = 1.8, vmax = 5, inf = 99999999;
double z[n];

double myrand(){
    return (1.0 / range) * (-2 * (rand() % 2) + 1) * (rand() % (range + 1));
}

struct pair{
    double x, y;

    pair add(pair f){
        pair nf;
        nf.x = x + f.x;
        nf.y = y + f.y;
        return nf;
    }

    pair time(double t){
        pair nf;
        nf.x = x * t;
        nf.y = y * t;
        return nf;
    }

    void limit_speed(){
        if (std::abs(x) > vmax || std::abs(y) > vmax){
            int scale_factor;
            if (y < x){
                scale_factor = x > 0 ? 1 : -1;
                y = (vmax / x) * y; 
                x = vmax;
            }
            else{
                scale_factor = y > 0 ? 1 : -1;
                x = (vmax / y) * x; 
                y = vmax;
            }
            x *= scale_factor;
            y *= scale_factor;
        }
    }

    double fitness(){
        return -1 * x * x + 4 * x + -4 * y * y + 8 * y + 10;
    }

    void display(){
        printf("(%5.2f, %5.2f)", x, y);
    }

    void init(int scale){
        x = myrand() * scale; y = myrand() * scale;
    }
}pos[n], v[n], pb[n], gb;

void data_init(){
    for (int i = 0; i < n; ++i){
        pos[i].init(100);
        v[i].init(1);
    }
}

void pair_display(pair* p){
    printf("Data:");
    for (int i = 0; i < n; ++i){
        p[i].display();  
        if (i != n - 1)
            printf(", "); 
    }
    printf("\n");
}

void new_pos(){
    for (int i = 0; i < n; ++i){
        double r1 = 0.01 * (rand() % 100), r2 = 0.01 * (rand() % 100);
        v[i].x = w * v[i].x + c1 * r1 * (pb[i].x - pos[i].x) + c2 * r2 * (gb.x - pos[i].x);
        v[i].y = w * v[i].y + c1 * r1 * (pb[i].y - pos[i].y) + c2 * r2 * (gb.y - pos[i].y);
        v[i].limit_speed();
        pos[i] = pos[i].add(v[i].time(lr));
    }
}

void new_fitness(){
    for (int i = 0; i < n; ++i){
        z[i] = pos[i].fitness();
    }
}

void new_record(){
    for (int i = 0; i < n; ++i){
        if (z[i] > pb[i].fitness()){
            pb[i] = pos[i];
            if (z[i] > gb.fitness()){
                gb = pb[i];
            }
        }
    }
}

void result_display(int epoch){
    printf("Epoch%d Gb:%.4f Pos:(%.4f,%.4f)\n", epoch, gb.fitness(), gb.x, gb.y);
}

int main(){
    srand(42);
    data_init();
    for (int i = 0; i < k; ++i){
        new_pos();
        new_fitness();
        new_record();
        result_display(i + 1);
    }
    //pair_display(pos);
    //pair_display(v);
    return 0;
}
