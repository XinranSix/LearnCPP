#include <format>
#include <iostream>

struct MilesExtimator {
    virtual ~MilesExtimator() = default;
    int getMilesLeft() const {
        return getMilesPerGallon() * getGallonsLeft();
    }
    virtual void setGallosLeft(int gallons) {
        m_gallonsLeft = gallons;
    }
    virtual int getGallonsLeft() const {
        return m_gallonsLeft;
    }

private:
    int m_gallonsLeft { 0 };
    virtual int getMilesPerGallon() const {
        return 20;
    }
};

class EfficientCarMilesEstimator : public MilesExtimator {
private:
    int getMilesPerGallon() const override {
        return 35;
    }
};

int main(int argc, char *argv[]) {

    MilesExtimator myMilesExtimator;
    myMilesExtimator.setGallosLeft(2);
    std::cout << std::format("Normal estimator can go {} more miles.",
                             myMilesExtimator.getMilesLeft())
              << std::endl;

    EfficientCarMilesEstimator myEfficient;
    myEfficient.setGallosLeft(2);
    std::cout << std::format("Efficient estimator can go {} more miles.",
                             myEfficient.getMilesLeft())
              << std::endl;

    return 0;
}
