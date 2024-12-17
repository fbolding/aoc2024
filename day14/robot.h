#ifndef ROBOT_H
#define ROBOT_H

class robot {
    public:
        /**
         * @brief Construct a new robot object
         * 
         * @param _id Identification number of robot
         * @param _x Initial x position (column)
         * @param _y Initial y position (row)
         * @param _vx Horizontal velocity
         * @param _vy Vertical velocity
         * @param _height Height of movement space
         * @param _width Width of movement space
         */
        robot(int _id, int _x, int _y, int _vx, int _vy, int _width, int _height)
            : id(_id), x(_x), y(_y), vx(_vx), vy(_vy), width(_width), height(_height){};

        /**
         * @brief Simulate movement of robot for one second, wrapping as needed 
         * 
         */
        void simulate(){
            x += vx;
            y += vy;
            if (x < 0){ x = width + x;}
            else if (x > width-1){ x = x-width;}
            if (y < 0){ y = height + y;}
            else if (y > height-1){ y = y - height;}
        }

        /**
         * @brief Get the Quadrant in which the robot is located
         * 
         * @return int Quadrant of robot. 0 = top-left, 1 = top-right, 2 = bottom-left, 3 = bottom-right. -1 means no quadrant (center line)
         */
        int getQuadrant(){
            // Int division truncates, therefore width/2 is the middle
            if(x < width/2 && y < height/2){ return 0;}
            else if(x > width/2 && y < height/2){ return 1;}
            else if(x < width/2 && y > height/2){ return 2;}
            else if(x > width/2 && y > height/2){ return 3;}
            else { return -1;}
        } 

        void printInfo(){
            printf("ID:%i | (%i,%i) vx=%i, vy=%i, Q=%i\n", id,x,y,vx,vy, getQuadrant());
        }
        int id;
        int x;
        int y;
        int vx;
        int vy;
        int height;
        int width;
};
#endif