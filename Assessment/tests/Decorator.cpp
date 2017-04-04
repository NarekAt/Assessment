#include <string>
#include <memory>

#include <gtest/gtest.h>

class Car
{
protected:
    std::string str_;

public:
    Car(const std::string model = "Unknkown car")
    {
        str_ = model;
    }

    virtual std::string getDescription()
    {
        return str_;
    }

    virtual double getCost() = 0;
};

class OptionsDecorator : public Car
{
private:
    std::unique_ptr<Car> base_;

public:
    OptionsDecorator(std::unique_ptr<Car> c)
    {
        base_ = std::move(c);
    }
    virtual double getCost()
    {
        return base_->getCost();
    }

    virtual std::string getDescription() override
    {
        return base_->getDescription();
    }
};

class RealCarModel : public Car
{
public:
    RealCarModel()
        : Car("RealCarModel")
    {}

    virtual double getCost()
    {
        return 2000;
    }
};

class Navigation : public OptionsDecorator
{
public:
    Navigation(std::unique_ptr<Car> c)
        : OptionsDecorator(std::move(c))
    {}

    virtual std::string getDescription()
    {
        return OptionsDecorator::getDescription() + ", Navigation";
    }

    virtual double getCost()
    {
        return 30 + OptionsDecorator::getCost();
    }
};

class HighSoundSystem : public OptionsDecorator
{
public:
    HighSoundSystem(std::unique_ptr<Car> c)
        : OptionsDecorator(std::move(c))
    {}

    virtual std::string getDescription()
    {
        return OptionsDecorator::getDescription() + ", HighSoundSystem";
    }

    virtual double getCost()
    {
        return 10 + OptionsDecorator::getCost();
    }
};


TEST(DecoratorTest, DesignPatterns)
{
    std::unique_ptr<Car> realCar = std::make_unique<RealCarModel>();

    EXPECT_EQ(realCar->getDescription(), "RealCarModel");
    EXPECT_EQ(realCar->getCost(), 2000);

    std::unique_ptr<Car> carWithNavigation = std::make_unique<Navigation>(std::move(realCar));

    EXPECT_EQ(carWithNavigation->getDescription(), "RealCarModel, Navigation");
    EXPECT_EQ(carWithNavigation->getCost(), 2030);

    std::unique_ptr<Car> carWithNavigationAndHighSound = std::make_unique<HighSoundSystem>(std::move(carWithNavigation));

    EXPECT_EQ(carWithNavigationAndHighSound->getDescription(), "RealCarModel, Navigation, HighSoundSystem");
    EXPECT_EQ(carWithNavigationAndHighSound->getCost(), 2040);
}