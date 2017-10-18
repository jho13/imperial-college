#ifndef ROTOR_H
#define ROTOR_H

class Rotor
{
  private:
    int config[26];
    bool notches[26];
    int relpos; //the relative position of the rotor - e.g. relpos = 1
    						//means the letter 'A' would enter where letter 'B' 
    						//previously was 
  public:
    //CONSTRUCTOR
    void set(int rotor_config[], bool rotor_notches[])
    {
      for (int i = 0; i < 26; i++)
      {
    	config[i] = rotor_config[i];
    	notches[i] = rotor_notches[i];
      }
      relpos = 0;
    }

    //FUNCTION WHICH RETURNS 'true' IF THERE IS A NOTCH AT "relpos"
    bool is_notch();

    //FUCNTION WHICH 'rotates' THE ROTOR ONCE. HENCE THE ROTOR MAPPING
    //IS CHANGED AND THE RELATIVE POSITION IS INCREMENTED BY 1.
    void rotate();

    //FUNCTION WHICH ENCODES "number" (AS IT GOES "INTO" THE MACHINE)
    //ACCORDING TO THE ROTOR MAPPING.
    int encode_in(int number);

    //FUNCTION WHICH ENCODES "number" (AS IT GOES "OUT OF" THE MACHINE)
    //ACCORDING TO THE ROTOR MAPPING.
    int encode_out(int number);
};

#endif
