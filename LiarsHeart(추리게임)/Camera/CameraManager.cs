using System;
using System.Collections;
using UnityEngine;

public class CameraManager : Singleton<CameraManager>
{
    [SerializeField] private Camera mainCamera;
    public Camera MainCamera { get => mainCamera; set => mainCamera = value; }

    [SerializeField] private Vector3 defaultPosition;
    [SerializeField] private float defaultSize;

    [SerializeField] private CameraZoom cameraZoom;
    [SerializeField] private CameraShake cameraShake;
    [SerializeField] private CameraFade cameraFade;


    protected override void Awake()
    {
        base.Awake();

        // 카메라 컴포넌트 탐색
        Camera mainCamera = FindFirstObjectByType<Camera>();
        if(mainCamera == null)
        {
            Debug.LogError("카메라 탐색 실패");
        }
    }

    private void Start()
    {
        // 카메라 기본값 저장
        defaultPosition = MainCamera.transform.position;
        defaultSize = MainCamera.orthographicSize;

        // 카메라 연출 생성
        cameraZoom = new CameraZoom(MainCamera);
        cameraShake = new CameraShake(MainCamera);
        cameraFade = new CameraFade();
    }

    // 입력 값의 따라 카메라 줌인
    // TODO : 이후 Size와 Speed는 자주 사용되는 값을 기폴트 매개변수로 지정해 놓으면 좋을듯
    public void Zoom(Vector3 targetPos, float zoomSize, float zoomSpeed)
    {
        cameraZoom.Play(this, targetPos, zoomSize, zoomSpeed);
    }

    // 기본 값의 따라 카메라 줌아웃
    // TODO : Speed는 자주 사용되는 값을 기폴트 매개변수로 지정해 놓으면 좋을듯
    public void Zoom(float zoomSpeed)
    {
        cameraZoom.Play(this, defaultPosition, defaultSize, zoomSpeed);
    }

    // 입력 값에 따라 카메라 흔들기
    // TODO : Power, Duration은 자주 사용되는 값을 기폴트 매개변수로 지정해 놓으면 좋을듯
    public void Shake(float shakePower, float shakeDuration)
    {
        cameraShake.Play(this, shakePower, shakeDuration);
    }

    // 입력 값에 따라 카메라 페이드효과
    public void Fade(float fadeDuration)
    {
        cameraFade.Fade(this, fadeDuration);
    }

    // 페이드 중 실행할 함수 지정
    public void Fade(float fadeDuration, Func<IEnumerator> func)
    {
        cameraFade.Fade(this, fadeDuration, func);
    }

    // 입력 값에 따라 카메라 페이드아웃
    public void FadeOut(float fadeDuration, bool fullScreenFade = true)
    {
        cameraFade.FadeOut(this, fadeDuration, fullScreenFade);
    }

    // 입력 값에 따라 카메라 페이드인
    public void FadeIn()
    {
        cameraFade.FadeIn(this);
    }
}