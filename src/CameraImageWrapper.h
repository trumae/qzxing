#ifndef CAMERAIMAGE_H
#define CAMERAIMAGE_H

#include <QImage>
#include <QString>
#include <zxing/zxing/common/GreyscaleLuminanceSource.h>

using namespace zxing;

class CameraImageWrapper : public LuminanceSource
{
public:
    CameraImageWrapper();
    CameraImageWrapper(const QImage& sourceImage);
    CameraImageWrapper(CameraImageWrapper& otherInstance);
    ~CameraImageWrapper();

    static CameraImageWrapper* Factory(const QImage& image, int maxWidth=-1, int maxHeight=-1, bool smoothTransformation=false);
    
    QImage getOriginalImage();
    Ref<GreyscaleLuminanceSource> getDelegate() { return delegate; }

    ArrayRef<byte> getRow(int y, ArrayRef<byte> row) const;
    ArrayRef<byte> getMatrix() const;

    bool isCropSupported() const;
    Ref<LuminanceSource> crop(int left, int top, int width, int height) const;
    bool isRotateSupported() const;
    Ref<LuminanceSource> invert() const;
    Ref<LuminanceSource> rotateCounterClockwise() const;
  
private:
    ArrayRef<byte> getRowP(int y, ArrayRef<byte> row) const;
    ArrayRef<byte> getMatrixP() const;
#if (QT_VERSION >= QT_VERSION_CHECK(5, 5, 0))
    QImage* grayScaleImage(const QImage *origin);
#endif
    unsigned int gray(unsigned int r, unsigned int g, unsigned int b);

    QImage* image;
    Ref<GreyscaleLuminanceSource> delegate;
};

#endif //CAMERAIMAGE_H
