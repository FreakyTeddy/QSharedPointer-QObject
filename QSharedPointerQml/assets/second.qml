import bb.cascades 1.0
import MyModel 1.0

Page {
    property MyModel model3
    id: page
    
    attachedObjects: [
        MyModel {
            name: "Attached"
            age: 12
            id: myModel
        }
    ]
    
    Container {
        Label {
            id:lbl1
            text: myModel.name
        }
        Label {
            id:lbl2
            text: myModel.name
        }
        Label {
            id:lbl3
            text: model3.name
        }
        Button {
            text: "change"
            onClicked: {
                myModel.name = "cambie!"
            }
        }
    }
    
    onCreationCompleted: {
        //        var model2 = Application.createModel("hola", 15);
        //        lbl2.text = model2;
        //			shared pointers fail like this
        
        //we become the parent to handle automatic deletion
        model3 = Application.createModelPtr("lalalala", 16);
        model3.changeParent(page);
    }
    
    function onDestroy() {
    } 
}

