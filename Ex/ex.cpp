openFile(ifs)

while (ifs >> action) {
    if action == "Action1" {
        ifs >> arg1 >> arg2
    } else if action == "Action2" {
        ifs >> arg >> arg >> arg
    } else if action == "Action3" {
        // do
    } else {
        //
    }
}