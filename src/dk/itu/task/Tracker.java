package dk.itu.task;

import org.opencv.core.Mat;
import org.opencv.core.MatOfRect;

public class Tracker {
	
	private long mNativeTracker;
	
	public Tracker( String faceXml , String eyeXml ){
		mNativeTracker = createNativeTracker(faceXml, eyeXml);
	}
	
	public boolean initTracker(){
		return initNativeTracker(mNativeTracker);
	}
	
	public void destroyTracker(){
		destroyNativeTracker(mNativeTracker);
	}
	
	public void process(Mat rgba , Mat gray ){
		processNativeTracker(mNativeTracker, rgba.getNativeObjAddr() , gray.getNativeObjAddr() );
		
	}

	private static native long createNativeTracker(String faceXml , String eyeXml );
	private static native void destroyNativeTracker(long thiz);
	private static native boolean initNativeTracker(long thiz);
	private static native void processNativeTracker(long thiz , long rgba , long gray);
	

}
