import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12

import Demo 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("PrefixTickLabels")

    Item {
        anchors.fill: parent
        anchors.margins: 20
        Page {
            anchors.fill: parent
            spacing: 20
            GroupBox {
                title: "Demo"
                anchors.fill: parent

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 10

                    Rectangle {
                        color: "#eeeeee"
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        ColumnLayout {
                            anchors.fill: parent
                            anchors.margins: 5
                            spacing: 0

                            Item {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                Repeater {
                                    model: parent.width
                                    Rectangle {
                                        width: 1
                                        height: 1
                                        color: "#0000AA"
                                        x: index
                                        readonly property double xx: horizontalTickBar.minValue + x*horizontalTickBar.unitsPerPixel
                                        readonly property double yy: Math.sin(3/Math.tan(xx)) - Math.cos(4/Math.cos(Math.sqrt(Math.abs(xx))))
                                        y: parent.height/4 * (2 + yy)
                                    }
                                }
                            }

                            Rectangle {
                                Layout.fillWidth: true
                                Layout.preferredHeight: 1
                                color: horizontalTickBar.tickColor
                            }

                            Item {
                                id: horizontalTickBar
                                Layout.fillWidth: true
                                Layout.preferredHeight: 2*prefix.height + tickHeight

                                property real midValue: 10.0
                                property real unitsPerPixel: 0.01 // 3.1415926535692
                                property real tickHeight: 5
                                readonly property real minValue: midValue - width/2*unitsPerPixel
                                readonly property real maxValue: midValue + width/2*unitsPerPixel

                                property color tickColor: "#000000"
                                property color prefixColor: "#00AA00"
                                function xForValue(value) {
                                    return width/2 + (value - midValue) / unitsPerPixel
                                }

                                Rectangle {
                                    id: prefixTick
                                    x: horizontalTickBar.xForValue(prefixTickLabelsModel.prefix)
                                    y: 0
                                    width: 1
                                    height: parent.height - prefixTickLabel.height
                                    visible: prefixTickLabelsModel.hasPrefix && 0 <= x && x < parent.width
                                    color: horizontalTickBar.tickColor
                                }
                                Row {
                                    id: prefixTickLabel
                                    x: Math.min(parent.width - width, Math.max(0, horizontalTickBar.xForValue(prefixTickLabelsModel.prefix) - width/2))
                                    y: parent.height - height
                                    visible: prefixTickLabelsModel.hasPrefix
                                    Label {
                                        id: prefix
                                        text: prefixTickLabelsModel.prefixLabelLeading
                                        color: horizontalTickBar.tickColor
                                    }
                                    Label {
                                        text: prefixTickLabelsModel.prefixPlaceholder
                                        color: horizontalTickBar.prefixColor
                                    }
                                    Label {
                                        text: prefixTickLabelsModel.prefixLabelTrailing
                                        color: horizontalTickBar.tickColor
                                    }
                                }


                                Repeater {
                                    model: prefixTickLabelsModel
                                    Column {
                                        x: horizontalTickBar.xForValue(model.tick) - width/2
                                        anchors.top: parent.top
                                        visible: !(prefixTickLabelsModel.hasPrefix && Math.abs(model.tick - prefixTickLabelsModel.prefix) < 1e-9)
                                        Rectangle {
                                            height: horizontalTickBar.tickHeight
                                            width: 1
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            color: label.color
                                        }
                                        Label {
                                            id: label
                                            text: model.label
                                            color: prefixTickLabelsModel.hasPrefix ? horizontalTickBar.prefixColor : horizontalTickBar.tickColor
                                        }
                                    }
                                }

                                TextMetrics {
                                    id: testLabel
                                    text: "-xXXXmNm"
                                }

                                PrefixTickLabelsModel {
                                    id: prefixTickLabelsModel
                                    min: horizontalTickBar.minValue
                                    max: horizontalTickBar.maxValue
                                    targetNbTicks: horizontalTickBar.width / testLabel.width
                                    prefixPlaceholder: "xxx"
                                    unit: "Nm"
                                }
                            }

                        }

                        MouseArea {
                            anchors.fill: parent
                            onWheel: {
                                if (wheel.modifiers && Qt.AltModifier) {
                                    const factor = (width + wheel.pixelDelta.y) / width
                                    horizontalTickBar.midValue += (wheel.x - width/2) * (1 - factor) * horizontalTickBar.unitsPerPixel
                                    horizontalTickBar.unitsPerPixel *= factor
                                }
                                else {
                                    horizontalTickBar.midValue += wheel.pixelDelta.y * horizontalTickBar.unitsPerPixel
                                }
                            }
                        }
                    }

                    Row {
                        Layout.alignment: Qt.AlignHCenter
                        spacing: 40
                        Grid {
                            columns: 2
                            columnSpacing: 10
                            Label { text: "Minimum" }
                            Label { text: prefixTickLabelsModel.min.toPrecision(4)  }
                            Label { text: "Maximum" }
                            Label { text: prefixTickLabelsModel.max.toPrecision(4) }
                            Label { text: "Target # ticks" }
                            Label { text: prefixTickLabelsModel.targetNbTicks }
                            Label { text: "Unit" }
                            Label { text: prefixTickLabelsModel.unit }
                        }
                        Grid {
                            columns: 2
                            columnSpacing: 10
                            Label { text: "Prefix" }
                            Label { text: prefixTickLabelsModel.hasPrefix ? prefixTickLabelsModel.prefix.toPrecision(4) : "-" }
                            Label { text: "Prefix label leading" }
                            Label { text: prefixTickLabelsModel.hasPrefix ? prefixTickLabelsModel.prefixLabelLeading : "-" }
                            Label { text: "Prefix placeholder" }
                            Label { text: prefixTickLabelsModel.prefixPlaceholder }
                            Label { text: "Prefix label trailing" }
                            Label { text: prefixTickLabelsModel.hasPrefix ? prefixTickLabelsModel.prefixLabelTrailing : "-" }
                        }
                    }
                }
            }
            footer: GroupBox {
                title: "Controls"
                Text {
                    anchors.fill: parent
                    text:
                        "- <b>Scroll</b>: pan left/right<br/>" +
                        "- <b>Scroll + Alt</b>: zoom in/out" +
                        ""
                }
            }
        }
    }
}
