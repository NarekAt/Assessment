#include <gtest/gtest.h>


class Command
{
public:
    virtual void execute() = 0;
};

// RECEIVER: Knows how to perform the operations
// associated with carrying out a request.
class Light
{
public:
    void turnOn()
    {
        std::cout << "The light is on" << std::endl;
    }

    void turnOff()
    {
        std::cout << "The light is off" << std::endl;
    }
};

// Concrete command(s): define a binding
// between a Receiver object and an action.
class LightOnCommand : public Command
{
private:
    Light& receiver;

public:
    LightOnCommand(Light& l)
        : receiver(l)
    {}

    virtual void execute() override
    {
        receiver.turnOn();
    }
};

class LightOffCommand : public Command
{
private:
    Light& receiver;

public:
    LightOffCommand(Light& l)
        : receiver(l)
    {}

    virtual void execute() override
    {
        receiver.turnOff();
    }
};

// Invoker: asks the command to carry out the request.
class Switch
{
public:
    Switch(Command& onCmd, Command& offCmd)
        : onCmd_(onCmd)
        , offCmd_(offCmd)
    {}

    void On()
    {
        onCmd_.execute();
    }

    void Off()
    {
        offCmd_.execute();
    }

private:
    Command& onCmd_;
    Command& offCmd_;
};

// Client:
TEST(CommandTest, DesignPatterns)
{
    // create concrete commands and set their receirvers
    Light l;
    LightOnCommand lOn(l);
    LightOffCommand lOff(l);

    Switch lightSwitch(lOn, lOff);
    lightSwitch.On();
    lightSwitch.Off();

    EXPECT_TRUE(true);
}