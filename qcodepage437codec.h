#ifndef QCODEPAGE437CODEC_H
#define QCODEPAGE437CODEC_H

#include "common.h"

#include <QTextCodec>
#include <QObject>

class QCodePage437Codec : public QTextCodec
{
public:
    QCodePage437Codec();
    ~QCodePage437Codec();

    QByteArray name() const;
    QList<QByteArray> aliases() const;
    int mibEnum() const;

private:

protected:
    QString convertToUnicode(const char *in, int length, ConverterState *state) const;
    QByteArray convertFromUnicode(const QChar *in, int length, ConverterState *state) const;
};

#endif // QCODEPAGE437CODEC_H

