package dk.itu.task;

import java.io.File;

import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewFrame;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewListener2;
import org.opencv.android.JavaCameraView;
import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.core.MatOfRect;
import org.opencv.core.Rect;
import org.opencv.core.Scalar;

import android.app.Fragment;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

public class PreviewFragment extends Fragment implements CvCameraViewListener2 {

	public static final String TAG = "PreviewFragment";

	private CameraBridgeViewBase mCameraView;

	private int mCameraId;

	private Mat rgba;
	private Mat gray;

	Tracker tracker;

	public static final String CAMERA_ID = "Camera_id";

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {

		View rootLayout = inflater.inflate(R.layout.fragment_preview,
				container, false);
		mCameraView = (CameraBridgeViewBase) rootLayout
				.findViewById(R.id.camera_surface);

		mCameraId = -1;

		if (savedInstanceState != null) {
			mCameraId = savedInstanceState.getInt(CAMERA_ID);
		}

		if (mCameraId == -1) {
			if (this.getArguments().containsKey(CAMERA_ID))
				mCameraId = (int) this.getArguments().getInt(CAMERA_ID);
		}

		if (mCameraId == -1)
			mCameraId = 0;

		mCameraView.setCameraIndex(mCameraId);
		mCameraView.setCvCameraViewListener(this);

		File dir = this.getActivity().getDir(MainActivity.CASCADE_DIR,
				Context.MODE_PRIVATE);
		File faces = new File(dir, MainActivity.FACE_XML);
		File eyes = new File(dir, MainActivity.EYE_XML);

		Log.i(TAG, faces.getAbsolutePath());
		Log.i(TAG, eyes.getAbsolutePath());

		if (faces.exists())
			Log.i(TAG, "Faces xml exists");
		else
			Log.i(TAG, "Faces xml does not exists");

		tracker = new Tracker(faces.getAbsolutePath(), eyes.getAbsolutePath());
		if (tracker.initTracker())
			Log.i(TAG, "Tracker is active");
		else
			Log.i(TAG, "Tracker is inactive");

		return rootLayout;
	}

	@Override
	public void onPause() {
		super.onPause();
		mCameraView.disableView();
		tracker.destroyTracker();
		Log.i(TAG, "onPause");
	}

	@Override
	public void onResume() {
		super.onResume();
		mCameraView.enableView();
		Log.i(TAG, "onResume");
	}

	@Override
	public void onCameraViewStarted(int width, int height) {
		Log.i(TAG, "Camera view started");
		rgba = new Mat();
		gray = new Mat();
	}

	@Override
	public void onCameraViewStopped() {
		Log.i(TAG, "Camera view stopped");
		rgba.release();
		gray.release();
	}

	@Override
	public Mat onCameraFrame(CvCameraViewFrame inputFrame) {
		Log.i(TAG, "Camera view onFrame");

		rgba = inputFrame.rgba();
		gray = inputFrame.gray();

		tracker.process(rgba , gray);
		return rgba;
	}

}
