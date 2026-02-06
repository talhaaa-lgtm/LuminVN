# LuminVN
2/2.5D Visual Novel Engine

# Documentation

1. Scenes

  scene <scene_name>{
    instructions
  }

  jump scene(<scene_name>)          #can be used inside scenes to jump to another one, does not return to previous scene

  call scene(<scene_name>)          #automatically returns to previous scene

  e.g.
    scene third_choice_8{
      instructions

      call scene(second_scene)
    }


2. Positions

  position{
    <position_name>: (x, y)
     .
     .
  }

  e.g.
    position{
      left: (0, 0)
      mid: (100, 0)
      right: (200, 0)
    }

  No positions set by default.


3. Characters

  declare <name> = character("<name>", color: "<color>"){
    state default = "<filename>"
    state <state_name> = "<filename>"
     .
     .
  }
  #color can take strings and hex


  show <name> at (x, y) with <effect>
  hide <name>

  e.g.
    declare am = character("Ami", color: "white"){
      state default = "ami_neutral.png"
      state happy = "ami_happy.png"
    }

    show am at (200, 300) with fade #no state mention defaults
    show am.happy at left with slide

    hide am     #no need to define state of character


4. Background, Music and Sound Effects

Background
  declare <name> = background("<filename>")

  show <name> with <effect>
  hide <name> with <effect>

  e.g.
    declare bg1 = background("start.png")

    show bg1 with fade
    hide bg1 with glitch

Music
  declare <name> = music("<name>")
  play <name>           #loops
  stop <name>           #only to stop for a certain period, no need to use to play some other track

  Music persists until changed

Sound Effects
  play sfx <name>


5. Variables

  <variable_name> = value           #data type is automatically resolved

  e.g.
    foo = 5
    quux = 0.3
    username = "Sata"

    variables are global, scope-bound variables yet to be added
    variables cannot be reserved words (i.e. play, jump, etc)


6. Dialogue

  <speaker_name>: "<dialogue>" ~animated: <speed> ~font: <font>

  By default, dialogue is not animated and if font is not declared, default is used

  e.g
    am: "Hello!"
    am: "Hey, you're finally awake...." ~animated: 10
    am: "Hiiii {variable}!!"
    "Text without speaker, narration"
    "???": "Dialogue without declaring a character" ~font: roman


7. Flags

  flag <flag_name> = <state>

  e.g.
    flag met_ami = false


8. Meters

  meter <meter_name> = <default_value>{
    <attribute_name>: <range>
     .
     .
  }

  increase <meter_name> #increases by 1
  decrease <meter_name> #decreases by 1

  increase <meter_name> by <value>

  e.g.
    meter affection = 150{
      low: (0, 100)
      mid: (101, 200)
      high: (201, 300)
    }
   #meters must always be defined with ranges, no defaults are set

    decrease affection by 50
    decrease affection by Decrease_level #variable


9. Conditionals

  if (<expression>){
    instructions
  }
  else if (<expression>){
    instructions
  }
  else{
    instructions
  }

  #operators such as >=, <=, >, <, ==, != are allowed

  e.g.
    if (met_ami is false){
      jump scene(ami)
    }
    else if (affection is low){
      am: "Not cool...."
    }
    else{
      am: "I- I like you.... {username}" ~animated: 5
    }


10. Choices

  choice{
    "<choice_string>":
      instructions
    "<choice_string>":
      instructions
     .
     .
  }

  e.g.
    choice{
      "Tease her":
        call scene(teasing)
      "Pat her head":
        "Pats"
        "{username}": There there....
        increase affection by 120
      "Shrug her off":
        decrease affection by 200
        am: "Hmpfh..."
    }


11. Fonts

  declare <name> = font("<filename>", color: "<color>", size: "<size>")

  #default fonts used if none is declared

  e.g.
    declare ami_font = font("roman.ttf", color: "white", size: "12")
