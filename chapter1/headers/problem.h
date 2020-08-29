#include<vector>
enum cell_color {red, green, blue};
class cell{
	public:
		int ID;
		cell_color color;
		inline cell(int ID):ID(ID),color(red){}
};

class problem{
	public:
		std::vector<cell*> cells;
		std::vector<std::vector<cell*>> relations;
		problem();
		problem(problem* p);
		void print_colors();
		void make_relations();
		void assign_random_colors();
};
