#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Audio/SoundSource.hpp"
#include "FingerDetect.hpp"



int main()
{
    cv::VideoCapture cap(0);
    cv::namedWindow(windowCaptureName);
    cv::namedWindow(windowTreshold);
    trackbarBuild();
    Shot frame, frame_HSV, Hsv;
    frame.setName(windowCaptureName);
    Hsv.setName(windowTreshold);
    FingerDetect hand;
    sf::SoundBuffer buffer;
    buffer.loadFromFile("soundPaint.wav");
    sf::Sound soundPaint;
    soundPaint.setBuffer(buffer);
    sf::SoundBuffer buffer2;
    buffer2.loadFromFile("soundClean.wav");
    sf::Sound soundClean;
    soundClean.setBuffer(buffer2);
    while (true)
    {
        frame.SetFrame(cap);
        if (frame.empty())
            break;
        frame.convertToHsv(Hsv);
        Hsv.detectObject();
        Contour contour;
        contour.find(Hsv);
        Hull hull;
        hull.find(contour);
        hand.findTheFingers(hull, contour,frame);
        hand.whatColor();
        contour.draw(frame);
        hull.draw(frame);
        hand.drawing(frame);    
        frame.flip();
        Hsv.flip();
        cv::String text = "Fingers: ";
        if (hand.getFingersCount() == 1 && (soundPaint.getStatus() != sf::Sound::Playing))
        {
            soundClean.stop();
            soundPaint.play();
        }
        if (hand.getFingersCount() == 3 && (soundClean.getStatus() != sf::Sound::Playing))
        {
            soundPaint.stop();
            soundClean.play();
        }
        text += to_string(hand.getFingersCount());
        putText(frame.getFrame(), text, Point(20, 20), 1, 1, White);
        frame.show();
        Hsv.show();
        contour.clear();
        hull.clear();
        hand.zeroing();
        char key = static_cast<char>(waitKey(30));
        if (key == 'q' || key == 27)
            break;
    }
    return 0;
}

