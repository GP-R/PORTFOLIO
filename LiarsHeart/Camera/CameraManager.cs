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

        // ī�޶� ������Ʈ Ž��
        Camera mainCamera = FindFirstObjectByType<Camera>();
        if(mainCamera == null)
        {
            Debug.LogError("ī�޶� Ž�� ����");
        }
    }

    private void Start()
    {
        // ī�޶� �⺻�� ����
        defaultPosition = MainCamera.transform.position;
        defaultSize = MainCamera.orthographicSize;

        // ī�޶� ���� ����
        cameraZoom = new CameraZoom(MainCamera);
        cameraShake = new CameraShake(MainCamera);
        cameraFade = new CameraFade();
    }

    // �Է� ���� ���� ī�޶� ����
    // TODO : ���� Size�� Speed�� ���� ���Ǵ� ���� ����Ʈ �Ű������� ������ ������ ������
    public void Zoom(Vector3 targetPos, float zoomSize, float zoomSpeed)
    {
        cameraZoom.Play(this, targetPos, zoomSize, zoomSpeed);
    }

    // �⺻ ���� ���� ī�޶� �ܾƿ�
    // TODO : Speed�� ���� ���Ǵ� ���� ����Ʈ �Ű������� ������ ������ ������
    public void Zoom(float zoomSpeed)
    {
        cameraZoom.Play(this, defaultPosition, defaultSize, zoomSpeed);
    }

    // �Է� ���� ���� ī�޶� ����
    // TODO : Power, Duration�� ���� ���Ǵ� ���� ����Ʈ �Ű������� ������ ������ ������
    public void Shake(float shakePower, float shakeDuration)
    {
        cameraShake.Play(this, shakePower, shakeDuration);
    }

    // �Է� ���� ���� ī�޶� ���̵�ȿ��
    public void Fade(float fadeDuration)
    {
        cameraFade.Fade(this, fadeDuration);
    }

    // ���̵� �� ������ �Լ� ����
    public void Fade(float fadeDuration, Func<IEnumerator> func)
    {
        cameraFade.Fade(this, fadeDuration, func);
    }

    // �Է� ���� ���� ī�޶� ���̵�ƿ�
    public void FadeOut(float fadeDuration, bool fullScreenFade = true)
    {
        cameraFade.FadeOut(this, fadeDuration, fullScreenFade);
    }

    // �Է� ���� ���� ī�޶� ���̵���
    public void FadeIn()
    {
        cameraFade.FadeIn(this);
    }
}