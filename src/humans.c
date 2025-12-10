#include "humans.h"
#include <math.h>
#include <stdlib.h>

#define DEGTORAD 0.0174532925

void UpdateHumans(Human* humans, const int humanCount, bool boundaryCheck){
    for(int i = 0; i < humanCount; i++){
        Human* h = &humans[i];
        if(h->controlled == false){
            h->direction += (float)(rand() % 61 - 30);  // -30 to +30
            h->position.x += sin(h->direction * DEGTORAD);
            h->position.y += cos(h->direction * DEGTORAD);
            
            if(boundaryCheck){
                if(h->position.x < 0){
                    h->position.x = 1024.f;
                }else if(h->position.x > 1024.f){
                    h->position.x = 0;
                }
                
                if(h->position.y < 0){
                    h->position.y = 1024.f;
                }else if(h->position.y > 1024.f){
                    h->position.y = 0;
                }
            }
        }
        DrawCircle((int)h->position.x, (int)h->position.y, 8.f, BROWN);
    }
}