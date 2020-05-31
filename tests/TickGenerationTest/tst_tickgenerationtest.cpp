#include <QtTest>

#include "PrefixTickLabels.h"

class TickGenerationTest : public QObject
{
    Q_OBJECT
private slots:
    void prototype_data();
    void prototype();

    void specialCases_leftMostPrefix();
    void specialCases_preferPositionedPrefix();
    void specialCases_repeatLabels();
    void specialCases_prefixMatchesTick();

    void prefixLabel1();
    void prefixLabel2();
    void prefixLabel3();
};

using TicksWithLabel = PrefixTickLabels::TicksAndLabel;
void TickGenerationTest::prototype_data()
{
    QTest::addColumn<double>("min");
    QTest::addColumn<double>("max");
    QTest::addColumn<double>("prefix");
    QTest::addColumn<QString>("prefixLabel");
    QTest::addColumn<TicksWithLabel>("ticksWithLabel");

    QTest::newRow("100M") << -3.151215632696511e+08 << 3.151278464549583e+08
                          << 0.0 << "" << TicksWithLabel({
                                 { -3e+08, "-300M" },
                                 { -2e+08, "-200M" },
                                 { -1e+08, "-100M" },
                                 { 0.0, "0" },
                                 { 1e+08, "100M" },
                                 { 2e+08, "200M" },
                                 { 3e+08, "300M" },
                                 });
    QTest::newRow("10M") << -3.316787997179953e+07 << 3.317416315710672e+07
                         << 0.0 << "" << TicksWithLabel({
                                { -3e+07, "-30M" },
                                { -2e+07, "-20M" },
                                { -1e+07, "-10M" },
                                { 0.0, "0" },
                                { 1e+07, "10M" },
                                { 2e+07, "20M" },
                                { 3e+07, "30M" },
                                });
    QTest::newRow("1M") << -3.48854488781516e+06 << 3.49482807312234e+06
                        << 0.0 << "" << TicksWithLabel({
                               { -3e+06, "-3M" },
                               { -2e+06, "-2M" },
                               { -1e+06, "-1M" },
                               { 0.0, "0" },
                               { 1e+06, "1M" },
                               { 2e+06, "2M" },
                               { 3e+06, "3M" },
                               });
    QTest::newRow("100k") << -3.644043526589102e+05 << 3.706875379660898e+05
                          << 0.0 << "" << TicksWithLabel({
                                 { -3e+05, "-300k" },
                                 { -2e+05, "-200k" },
                                 { -1e+05, "-100k" },
                                 { 0.0, "0" },
                                 { 1e+05, "100k" },
                                 { 2e+05, "200k" },
                                 { 3e+05, "300k" },
                                 });
    QTest::newRow("10k") << -3.55474542214102e+04 << 4.18306395285898e+04
                         << 0.0 << "" << TicksWithLabel({
                                { -3e+04, "-30k" },
                                { -2e+04, "-20k" },
                                { -1e+04, "-10k" },
                                { 0.0, "0" },
                                { 1e+04, "10k" },
                                { 2e+04, "20k" },
                                { 3e+04, "30k" },
                                { 4e+04, "40k" },
                                });
    QTest::newRow("1k") << -9.309385964102071e+02 << 7.214123903589792e+03
                        << 0.0 << "" << TicksWithLabel({
                               { 0e+00, "0" },
                               { 1e+03, "1k" },
                               { 2e+03, "2k" },
                               { 3e+03, "3k" },
                               { 4e+03, "4k" },
                               { 5e+03, "5k" },
                               { 6e+03, "6k" },
                               { 7e+03, "7k" },
                               });
    QTest::newRow("100") << 2.712905153589793e+03 << 3.570280153589793e+03
                         << 3e+03 << "3xxx" << TicksWithLabel({
                                { 2.8e+03, "-200" },
                                { 2.9e+03, "-100" },
                                { 3.0e+03, "0" },
                                { 3.1e+03, "100" },
                                { 3.2e+03, "200" },
                                { 3.3e+03, "300" },
                                { 3.4e+03, "400" },
                                { 3.5e+03, "500" },
                                });
    QTest::newRow("10") << 3.096467653589793e+03 << 3.186717653589793e+03
                        << 3e+03 << "3xxx" << TicksWithLabel({
                               { 3.1e+03, "100" },
                               { 3.12e+03, "120" },
                               { 3.14e+03, "140" },
                               { 3.16e+03, "160" },
                               { 3.18e+03, "180" },
                               });
    QTest::newRow("1") << 3.136842653589793e+03 << 3.146342653589793e+03
                       << 3e+03 << "3xxx" << TicksWithLabel({
                              { 3.138e+03, "138" },
                              { 3.140e+03, "140" },
                              { 3.142e+03, "142" },
                              { 3.144e+03, "144" },
                              { 3.146e+03, "146" },
                              });
    QTest::newRow("100m") << 3.141092653589793e+03 << 3.142092653589793e+03
                          << 3.142e+03 << "3142.xxx" << TicksWithLabel({
                                 { 3.1412e+03, "-800m" },
                                 { 3.1414e+03, "-600m" },
                                 { 3.1416e+03, "-400m" },
                                 { 3.1418e+03, "-200m" },
                                 { 3.1420e+03, "0m" },
                                 });
    QTest::newRow("10m") << 3.141540022010845e+03 << 3.14164528516874e+03
                         << 3.141e+03 << "3141.xxx" << TicksWithLabel({
                                { 3.14156e+03, "560m" },
                                { 3.14158e+03, "580m" },
                                { 3.1416e+03, "600m" },
                                { 3.14162e+03, "620m" },
                                { 3.14164e+03, "640m" },
                                });
    QTest::newRow("1m") << 3.141587113423588e+03 << 3.141598193755998e+03
                        << 3.141e+03 << "3141.xxx" << TicksWithLabel({
                               { 3.141588e+03, "588m" },
                               { 3.14159e+03, "590m" },
                               { 3.141592e+03, "592m" },
                               { 3.141594e+03, "594m" },
                               { 3.141596e+03, "596m" },
                               { 3.141598e+03, "598m" },
                               });
    QTest::newRow("100µ") << 3.141592070414403e+03 << 3.141593236765183e+03
                          << 3.141593e+03 << "3141.593xxx" << TicksWithLabel({
                                 { 3.1415922e+03, "-800µ" },
                                 { 3.1415924e+03, "-600µ" },
                                 { 3.1415926e+03, "-400µ" },
                                 { 3.1415928e+03, "-200µ" },
                                 { 3.141593e+03, "0µ" },
                                 { 3.1415932e+03, "200µ" },
                                 });
    QTest::newRow("10µ") << 3.14159259220291e+03 << 3.141592714976676e+03
                         << 3.141592e+03 <<  "3141.592xxx" << TicksWithLabel({
                                { 3.1415926e+03, "600µ" },
                                { 3.14159262e+03, "620µ" },
                                { 3.14159264e+03, "640µ" },
                                { 3.14159266e+03, "660µ" },
                                { 3.14159268e+03, "680µ" },
                                { 3.1415927e+03, "700µ" },
                                });
    QTest::newRow("1µ") << 3.141592647128016e+03 << 3.14159266005157e+03
                        << 3.141592e+03 <<"3141.592xxx" << TicksWithLabel({
                               { 3.141592648e+03, "648µ" },
                               { 3.14159265e+03, "650µ" },
                               { 3.141592652e+03, "652µ" },
                               { 3.141592654e+03, "654µ" },
                               { 3.141592656e+03, "656µ" },
                               { 3.141592658e+03, "658µ" },
                               { 3.14159266e+03, "660µ" },
                               });
    QTest::newRow("100n") << 3.141592652909606e+03 << 3.14159265426998e+03
                          << 3.141592653e+03 << "3141.592653xxx" << TicksWithLabel({
                                 { 3.141592653e+03, "0n" },
                                 { 3.1415926532e+03, "200n" },
                                 { 3.1415926534e+03, "400n" },
                                 { 3.1415926536e+03, "600n" },
                                 { 3.1415926538e+03, "800n" },
                                 { 3.141592654e+03, "1000n" },
                                 { 3.1415926542e+03, "1200n" },
                                 });
    QTest::newRow("10n") << 3.141592653518194e+03 << 3.141592653661392e+03
                         << 3.141592653e+03 << "3141.592653xxx" << TicksWithLabel({
                                { 3.14159265352e+03, "520n" },
                                { 3.14159265354e+03, "540n" },
                                { 3.14159265356e+03, "560n" },
                                { 3.14159265358e+03, "580n" },
                                { 3.14159265360e+03, "600n" },
                                { 3.14159265362e+03, "620n" },
                                { 3.14159265364e+03, "640n" },
                                { 3.14159265366e+03, "660n" },
                                });
    QTest::newRow("1n") << 3.141592653582256e+03 << 3.141592653597329e+03
                         << 3.141592653e+03 << "3141.592653xxx" << TicksWithLabel({
                                { 3.141592653584e+03, "584n" },
                                { 3.141592653586e+03, "586n" },
                                { 3.141592653588e+03, "588n" },
                                { 3.14159265359e+03, "590n" },
                                { 3.141592653592e+03, "592n" },
                                { 3.141592653594e+03, "594n" },
                                { 3.141592653596e+03, "596n" },
                                });
}
void TickGenerationTest::prototype()
{
    const QFETCH(double, min);
    const QFETCH(double, max);
    const QFETCH(double, prefix);
    const QFETCH(QString, prefixLabel);
    const QFETCH(TicksWithLabel, ticksWithLabel);

    const int nbTicks = 9;
    const PrefixTickLabels ptl(min, max, nbTicks);

    QCOMPARE(ptl.hasPrefix(), prefix != 0.0);
    QCOMPARE(ptl.prefixValue(), prefix);
    QCOMPARE(ptl.prefixLabel(), prefixLabel);

    const auto ticks = ptl.ticksAndLabel();
    QCOMPARE(ticks.count(), ticksWithLabel.count());
    for (int i = 0; i < ticks.count(); i++)
    {
        QCOMPARE(ticks.at(i).first, ticksWithLabel.at(i).first);
        QCOMPARE(ticks.at(i).second, ticksWithLabel.at(i).second);
    }
}

void TickGenerationTest::specialCases_leftMostPrefix()
{
    const PrefixTickLabels ptl(0.0015, 0.0055, 9);
    QVERIFY(ptl.hasPrefix());
    QCOMPARE(ptl.prefixValue(), 0.002);
    QCOMPARE(ptl.prefixLabel("yyy"), QString("0.002yyy"));
}

void TickGenerationTest::specialCases_preferPositionedPrefix()
{
    const PrefixTickLabels ptl(5000.11 , 5001.11, 5);
    QVERIFY(ptl.hasPrefix());
    QCOMPARE(ptl.prefixValue(), 5001); // prefer visible one
}

void TickGenerationTest::specialCases_repeatLabels()
{
    {
        const PrefixTickLabels ptl(5.0, 10.0, 6);
        const auto ticks = ptl.ticksAndLabel();
        QCOMPARE(ticks.at(0).first, 5.0);
        QCOMPARE(ticks.at(0).second, "5");
        QCOMPARE(ticks.at(1).first, 6.0);
        QCOMPARE(ticks.at(1).second, "6");
        QCOMPARE(ticks.at(2).first, 7.0);
        QCOMPARE(ticks.at(2).second, "7");
        QCOMPARE(ticks.at(3).first, 8.0);
        QCOMPARE(ticks.at(3).second, "8");
    }
    {
        const PrefixTickLabels ptl(5.0, 10.0, 11);
        const auto ticks = ptl.ticksAndLabel();
        QCOMPARE(ticks.at(0).first, 5.0);
        QCOMPARE(ticks.at(0).second, "5.0");
        QCOMPARE(ticks.at(1).first, 5.5);
        QCOMPARE(ticks.at(1).second, "5.5");
        QCOMPARE(ticks.at(2).first, 6.0);
        QCOMPARE(ticks.at(2).second, "6.0");
        QCOMPARE(ticks.at(3).first, 6.5);
        QCOMPARE(ticks.at(3).second, "6.5");
    }
}

void TickGenerationTest::specialCases_prefixMatchesTick()
{
    const PrefixTickLabels ptl(4999.28, 5000.28, 6);
    QCOMPARE(ptl.prefixValue(), 5000.0);
    const auto ticks = ptl.ticksAndLabel();
    const auto tickAtPrefix = ticks.at(3);
    QCOMPARE(tickAtPrefix.first, 5000.0);
}

void TickGenerationTest::prefixLabel1()
{
    const PrefixTickLabels ptl(5361, 5526, 8, "Nm");
    QVERIFY(ptl.hasPrefix());
    QCOMPARE(ptl.prefixLabel("xxx"), QString("5xxx Nm"));
    QCOMPARE(ptl.prefixLabelLeading(), QString("5"));
    QCOMPARE(ptl.prefixLabelTrailing(), QString(" Nm"));
    const auto labels = ptl.ticksAndLabel();
    QCOMPARE(labels.count(), 3);
    QCOMPARE(labels.at(0).first, 5400.0);
    QCOMPARE(labels.at(0).second, QString("400 Nm"));
    QCOMPARE(labels.at(1).first, 5450.0);
    QCOMPARE(labels.at(1).second, QString("450 Nm"));
    QCOMPARE(labels.at(2).first, 5500.0);
    QCOMPARE(labels.at(2).second, QString("500 Nm"));
}

void TickGenerationTest::prefixLabel2()
{
    const PrefixTickLabels ptl(9.997, 10.51, 5, "Nm");
    QVERIFY(ptl.hasPrefix());
    QCOMPARE(ptl.prefixLabel("xxx"), QString("10.xxx Nm"));
    QCOMPARE(ptl.prefixLabelLeading(), QString("10."));
    QCOMPARE(ptl.prefixLabelTrailing(), QString(" Nm"));
    const auto labels = ptl.ticksAndLabel();
    QCOMPARE(labels.count(), 3);
    QCOMPARE(labels.at(0).first, 10);
    QCOMPARE(labels.at(0).second, QString("0 mNm"));
    QCOMPARE(labels.at(1).first, 10.2);
    QCOMPARE(labels.at(1).second, QString("200 mNm"));
    QCOMPARE(labels.at(2).first, 10.4);
    QCOMPARE(labels.at(2).second, QString("400 mNm"));
}

void TickGenerationTest::prefixLabel3()
{
    const PrefixTickLabels ptl(8610, 9198, 11, "s");
    QVERIFY(ptl.hasPrefix());
    QCOMPARE(ptl.prefixLabel("xxx"), QString("9xxx s"));
    QCOMPARE(ptl.prefixLabelLeading(), QString("9"));
    QCOMPARE(ptl.prefixLabelTrailing(), QString(" s"));
    const auto labels = ptl.ticksAndLabel();
    QCOMPARE(labels.count(), 5);
    QCOMPARE(labels.at(0).first, 8700.0);
    QCOMPARE(labels.at(0).second, QString("-300 s"));
    QCOMPARE(labels.at(1).first, 8800.0);
    QCOMPARE(labels.at(1).second, QString("-200 s"));
    QCOMPARE(labels.at(2).first, 8900.0);
    QCOMPARE(labels.at(2).second, QString("-100 s"));
    QCOMPARE(labels.at(3).first, 9000.0);
    QCOMPARE(labels.at(3).second, QString("0 s"));
    QCOMPARE(labels.at(4).first, 9100.0);
    QCOMPARE(labels.at(4).second, QString("100 s"));
}

QTEST_APPLESS_MAIN(TickGenerationTest)

#include "tst_tickgenerationtest.moc"
