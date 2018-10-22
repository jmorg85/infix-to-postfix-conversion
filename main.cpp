#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <cstdlib>


using namespace std;
int instring (char a, char b, char c, string line, int collision, int B);
int quad_instring (int index, int collision, int B);
int add_to_linear_table(string line, char a, char b, char c, int thing, int B, string hashtable[120]);
int add_to_quadratic_table(string line, char a, char b, char c, int thing, int B, string quad_hashtable[120]);

int main()
{
    int total_linear_sum = 0;
    int total_quadratic_sum = 0;
    char answer;
    int extra_linear_collision_sum = 0;
    string quad_hashtable[120];
    int linear_collision_sum = 0;
    string hashtable[120];
    int collision_counter = 0;
    int quad_collision_counter = 0;
    int quad_collision_sum = 0;
    int extra_quad_collision_sum = 0;
    int index[50];
    int B = 60;
    int thing = 0;
    string line;
    int linecounter = 0;
    char a, b, c;
    fstream input;
    input.open("a3.txt");

        input >> a;
        input >> b;
        input >> c;
        for (int i=0; i<120; i++)
        {
            hashtable[i] = "NULL";
        }
        for (int i=0; i<120; i++)
        {
            quad_hashtable[i] = "NULL";
        }

        cout << "This is linear hash with B=60. " << endl;
        for (int i=0; i<13; i++)
        {
            linecounter++;
            cout << linecounter << " ";
            for (int j=0; j<4; j++)
            {
                getline(input, line);
                if (line.empty()) line = "_______________";
                collision_counter = add_to_linear_table(line, a, b, c, thing, B, hashtable);
                line.resize(15, ' ');
                linear_collision_sum = linear_collision_sum + collision_counter;
                cout << line << " " <<collision_counter << "  ";
                if (input.eof()) goto new_hash;
            }


                cout << endl;
        }
        cout << endl;
        cout << "The total linear collisions are: " << linear_collision_sum << endl;


        new_hash:
            cout << endl << endl;
            input.clear();
            input.seekg(5, ios::beg);
            B = 120;
            for (int i=0; i<B; i++)
            {
                hashtable[i] = "NULL";
            }
            cout << "This is linear hash with B=120. " << endl;
            linecounter=0;
            for (int i=0; i<13; i++)
        {
            linecounter++;
            cout << linecounter << " ";
            for (int j=0; j<4; j++)
            {
                getline(input, line);
                if (line.empty()) line = "_______________";
                collision_counter = add_to_linear_table(line, a, b, c, thing, B, hashtable);
                line.resize(15, ' ');
                extra_linear_collision_sum = linear_collision_sum + collision_counter;
                cout << line << " " <<collision_counter << "  ";
                if (input.eof()) goto quad_hash;
            }


                cout << endl;
        }
        cout << endl;
        cout << "The total linear collisions are: " << linear_collision_sum << endl;

        quad_hash:
        cout << endl << endl;
        input.clear();
        input.seekg(5, ios::beg);
        B = 60;
        cout << "This is quadratic hashing with B=60. " << endl;
        linecounter = 0;
        for (int i=0; i<13; i++)
        {
            linecounter++;
            cout << linecounter<< " ";
            for (int j=0; j<4; j++)
            {
                getline(input, line);
                if (line.empty()) line = "_______________";
                quad_collision_counter = add_to_quadratic_table(line, a, b, c, thing, B, quad_hashtable);
                line.resize(15, ' ');
                quad_collision_sum = quad_collision_sum + quad_collision_counter;
                cout << line << " " << quad_collision_counter << " ";
                if (input.eof()) goto new_quad_hash;
            }
            cout << endl;
        }
        cout << endl;

        new_quad_hash:
            cout << endl << endl;
            input.clear();
            input.seekg(5, ios::beg);
            B = 120; cout << "This is quadratic hashing with B=120. " << endl;
            linecounter = 0;
             for (int i=0; i<13; i++)
        {
            linecounter++;
            cout << linecounter<< " ";
            for (int j=0; j<4; j++)
            {
                getline(input, line);
                if (line.empty()) line = "_______________";
                quad_collision_counter = add_to_quadratic_table(line, a, b, c, thing, B, quad_hashtable);
                line.resize(15, ' ');
                extra_quad_collision_sum = quad_collision_sum + quad_collision_counter;
                cout << line << " " << quad_collision_counter << " ";
                if (input.eof())
                {
                    break;
                }
            }
            cout << endl;
        }
        cout << endl;

        total_linear_sum = linear_collision_sum + extra_linear_collision_sum;
        total_quadratic_sum = quad_collision_sum + extra_quad_collision_sum;
        cout << "The total linear collisions: " << total_linear_sum << endl;
        cout << "The total quadratic collisions: " << total_quadratic_sum << endl;

        cout << "Press 'L' to see the linear hash table or press 'Q' to see the quadratic hash table. " << endl;
        cin >> answer;
        if (answer == 'L')
        {
            for (int i=0;i<120;i++)
            {
                if (hashtable[i] == "NULL")
                {
                    cout << i << ". " << "_______________" << endl;
                }
                else
                {
                    cout << i << ". " << hashtable[i] << endl;
                }
            }
        }
        if (answer == 'Q')
        {
            for (int i=0; i<120; i++)
            {
                if (hashtable[i] == "NULL")
                {
                    cout << i << ". " << "_______________" << endl;
                }
                else
                {
                    cout << i << ". " << quad_hashtable[i] << endl;
                }
            }
        }
    return 0;
}
///////////-----------------------------------------------------------------------------------------
int instring (char a, char b, char c, string line, int collision, int B)
{
    int answer;
    int a1;
    int a2;
    int a3;
    int length = line.length();
     for (int i=0; i<length; i++)
    {
        line[i] = toupper(line[i]);
    }
    for (int i=0; i<3; i++)
    {
        if (i == 0)
        {
            a1 =  a * line[0];
        }
        if (i == 1)
        {
            a2 =  b * line[1];
        }
        if (i == 2)
        {
            a3 = c * line[2];
            answer = a1 + a2 + a3;
            answer = answer % B + collision;
        }
    }
    return answer;
}
//////////////////-------------------------------------------------------------------------------------------
int quad_instring (char a, char b, char c, string line, int collision, int B)
{
    int answer;
    int a1;
    int a2;
    int a3;
    int length = line.length();
     for (int i=0; i<length; i++)
    {
        line[i] = toupper(line[i]);
    }
    for (int i=0; i<3; i++)
    {
        if (i == 0)
        {
            a1 =  a * line[0];
        }
        if (i == 1)
        {
            a2 =  b * line[1];
        }
        if (i == 2)
        {
            a3 = c * line[2];
            answer = a1 + a2 + a3;
            answer = answer % B + pow(collision, 2);
        }
    }
    return answer;
}
////////////////////////////----------------------------------------------------------------------------------
int add_to_linear_table(string line, char a, char b, char c, int thing, int B, string hashtable[120])
{
    thing =0;
    int collision = 0;
    int index;
    index = instring(a, b, c, line, thing, B);
        while (hashtable[index] != "NULL")
        {
            collision++;
            index = instring(a, b, c, line, collision, B);
        }
        hashtable[index] = line;
        return collision;
}
///////////////////////////////--------------------------------------------------------------------------------
int add_to_quadratic_table(string line, char a, char b, char c, int thing, int B, string quad_hashtable[120])
{
    int collision = 0;
    int index;
    index = instring(a, b, c, line, thing, B);
    while (quad_hashtable[index] != "NULL")
    {
        collision++;
        thing++;
        index = quad_instring(a, b, c, line, collision, B);
    }
    quad_hashtable[index] = line;
    return collision;
}

