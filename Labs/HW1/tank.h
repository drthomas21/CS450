#ifndef TANK_H
#define TANK_H
class Tank {
	private:
		double centerX;
		double centerY;
		double turrentDegree;

	public:
		void draw();
		void setX(double);
		void setY(double);
		void setTurrentDegree(double degree);
		double getX();
		double getY();
		double getTurrentDegree();
		double getTurrentTipX();
		double getTurrentTipY();

		Tank();
};
#endif