$(function(){
	// 修改密码弹窗，仅限第一次未修改过密码
	var reg=/^(?=.*[A-Za-z])(?=.*\d)[^]{8,20}$/;
	$('#submit').click(function(){
		var ar=[];
		$('#resetPwd input[type=password]').each(function(){
			ar.push($(this).val());
		});
		var old = ar[0];
		var a=ar[1];
		var b=ar[2];
		if(old == ''){
			myModal(2,'请输入旧密码！',2000);
		}else if(a == '' || a == null){
			myModal(2,'请输入新密码！',2000)
		}else if(b == '' || b == null){
			myModal(2,'请再次输入新密码！',2000)
		}else if(!reg.test(a) || !reg.test(b)){
			myModal(2,'新密码格式不正确,请重新输入8-20位的混合密码！',2000);
		}else if(a != b){
			myModal(2,'密码不一致，请重新输入!',2000);
		}else{
			$.ajax({
				type: "GET",
				url: '../cgi-bin/password.cgi',
				data: {
					username: 'admin',
					password: a,
					oldpassword:old,
					para: window.localStorage.getItem('sessionid')         	
				},
				success: function (data){
					if (data.status === 1) {
						window.localStorage.setItem('PwdModified','1')
						window.location.href = "webConfig.html";
					} else {
						myModal(2,'异常错误！',2000);
					}

				},
				error: function(error){
					myModal(2,'网络异常，请稍后再试！',2000);
				}
			});
		}

	});
	if( location.search && !window.localStorage.getItem('PwdModified')){
		$('#resetPwd').modal('show')
	}

	// 输入框检验
	function validateInput(){
		var alertField = '';
		var required = /.{1,}/;
		var ip = /^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$/
		var getLength = GetLength = function(str){
			return str.replace(/[^\x00-\xff]/g,"aa").length;
		}
		var isNumber=/^\d{1,}$/;
		var rpcName = $('#rpcName').val();
		var rpcPwd = $('#rpcPwd').val();
		var ipAddress = $('#ipAddress').val();
		var nodeSign = $('#nodeSign').val();
		var featureCode = $('#featureCode').val();
		var txHash = $('#txHash').val();
		var txIndex = $('#txIndex').val();
		var addIp = $('#addIp').val();
		var timestamp = $('#timestamp').val();
		var certificate = $('#certificate').val();
		var version = $('#version').val();
		var publicKey = $('#publicKey').val();
		if(!(rpcName.match(required) && getLength(rpcName) <= 20)){
			alertField = 'RPC账号';
		}else if(!(rpcPwd.match(required) && getLength(rpcPwd) <= 200)){
			alertField = 'RPC密码';
		}else if(!(ipAddress.match(required) && ipAddress.match(ip))){
			alertField = '公网IP地址';
		}else if(!(nodeSign.match(required) && getLength(nodeSign) <= 200)){
			alertField = '广播的主节点签名';
		}else if(!(featureCode.match(required) && getLength(featureCode) <= 200)){
			alertField = '主节点特征码';
		}else if(!(txHash.match(required) && getLength(txHash) <= 200)){
			alertField = '交易Hash';
		}else if(!(txIndex.match(required))){
			alertField = '交易索引';
		}else if(!(addIp.match(ip) || addIp =='')){
			alertField = '额外增加的同步节点';
		}else if(!timestamp.match(/^\d{10}$/) || timestamp < 1537545600){
			alertField = '证书到期日期';
		}else {
			return true
		}
		myModal(2,alertField+'格式错误，请重新输入！',2000)
		return false
	}
	// 输入框失焦验证
	$('input[type=text],textarea').on('blur',function(e){
		var required = /.{1,}/;
		var ip = /^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$/
		var getLength = GetLength = function(str){
			return str.replace(/[^\x00-\xff]/g,"aa").length;
		}
		switch (e.target.id) {
			case 'rpcName':
				if(!(e.target.value.match(required) && getLength(e.target.value) <= 20)){
					$(e.target).css('borderColor','red')
				}else {
					$(e.target).css('borderColor','rgb(217, 217, 217')
				}
			break;
			case 'rpcPwd':
				if(!(e.target.value.match(required) && getLength(e.target.value) <= 20)){
					$(e.target).css('borderColor','red')
				}else {
					$(e.target).css('borderColor','rgb(217, 217, 217')
				}
			break;
			case 'ipAddress':
				if(!(e.target.value.match(required) && e.target.value.match(ip))){
					$(e.target).css('borderColor','red')
				}else {
					$(e.target).css('borderColor','rgb(217, 217, 217')
				}
			break;
			case 'nodeSign':
				if(!(e.target.value.match(required) && getLength(e.target.value) <= 200)){
					$(e.target).css('borderColor','red')
				}else {
					$(e.target).css('borderColor','rgb(217, 217, 217')
				}
			break;
			case 'featureCode':
				if(!(e.target.value.match(required) && getLength(e.target.value) <= 200)){
					$(e.target).css('borderColor','red')
				}else {
					$(e.target).css('borderColor','rgb(217, 217, 217')
				}
			break;
			case 'txHash':
				if(!(e.target.value.match(required) && getLength(e.target.value) <= 200)){
					$(e.target).css('borderColor','red')
				}else {
					$(e.target).css('borderColor','rgb(217, 217, 217')
				}
			break;
			case 'txIndex':
				if(!(e.target.value.match(required) && getLength(e.target.value) <= 200)){
					$(e.target).css('borderColor','red')
				}else {
					$(e.target).css('borderColor','rgb(217, 217, 217')
				}
			break;
			case 'certificate':
				if(!(e.target.value.match(required) && getLength(e.target.value) <= 200)){
					$('#timestamp,#version').val('').attr('disabled',true)
				}else {
					$('#timestamp,#version').val('').attr('disabled',false)
				}
			default:
			break;
		}
	})

	// 提示框myModal
	// @param label 0:warning 1:success 2： danger
	// @param text 提示文字
	// @param time 显示时间
	function myModal(label,text,time){
		time = time || 10000
		var collection = 'fa-check-circle text-success fa-exclamation-circle text-warning fa-times-circle text-danger'
		if(label==1){
			$('#myModal .modal-content .fa').removeClass(collection).addClass('fa-check-circle text-success')
		}else if(label==0){
			$('#myModal .modal-content .fa').removeClass(collection).addClass('fa-exclamation-circle text-warning')
		}else if(label==2){
			$('#myModal .modal-content .fa').removeClass(collection).addClass('fa-times-circle text-danger')
		}
		$('#myModal .content').html(text);
		$('#myModal').modal('show')
		setTimeout(function(){
			$('#myModal').modal('hide')
		}, time)
	}


	// 修改主节点配置
	function book() {	
		$.ajax({
			url:'../cgi-bin/writecfg.cgi?para='+window.localStorage.getItem('sessionid'),
			type:'POST',
			data:{					
				rpcuser:$('#rpcName').val(),
				rpcpassword:$('#rpcPwd').val(),
				masternodeprivkey:$('#featureCode').val(),
				addnode:$('#addIp').val(),
				certificate:$('#certificate').val(),
				certifiversion:$('#version').val(),
				collateraloutputindex:$('#txIndex').val(),
				collateraloutputtxid:$('#txHash').val(),
				externalip:$('#ipAddress').val(),
				broadcastsign:$('#nodeSign').val(),
				uctpubkey1:$('#publicKey').val(),
				certifiperiod:$('#timestamp').val()

			},
			success: function(data){
				if(data.msg=='success'){
					$('#alert .modal-body').text('保存配置成功！')
					$('#alert').modal('show')
				}else if(data.session=="failed"){
					window.localStorage.removeItem('sessionid')
					window.location.href="/"
				}else {
					$('#alert .modal-body').text('保存配置失败！')
					$('#alert').modal('show')
				}
			},
			error: function(error){
				myModal(2,'网络异常，请稍后再试！',2000);
			}
		})
	}

			// 主节点操作
			function mainNodeOperate(code){
				if(code ==1 ){
					$.ajax({
						type:'GET',
						url:'../cgi-bin/startnode.cgi?para='+window.localStorage.getItem('sessionid'),
						success:function(data){
							if(data.ulord =='start'){
								// $('#confirm').modal('hide')
								// $('#myModal .content').html('正在启动主节点，<span style="rgba(255,0,0,0.7)">这可能需要几小时</span>，请根据主节点信号灯判断是否启动成功！');
								// $('#myModal').modal('show')
								// mainNodeStatus.status = 1

								// setTimeout(function(){
								// 	$('#myModal').modal('hide')
								// },5000)
							}else {
								window.localStorage.removeItem('sessionid')
								window.location.href="/"
							}
						},
						error:function(err,text){
							// myModal(2,'网络异常，请稍后再试！',2000);
						}
					})
					$('#confirm').modal('hide')
					myModal(0,'正在启动主节点，<span style="rgba(255,0,0,0.7)">这可能需要几小时</span>，请根据主节点信号灯判断是否启动成功！',5000)
					setLocalStatus('status',1)
					$('#rpcName,#rpcPwd').attr('readonly',true)
					setTimeout(function(){
						$('#myModal').modal('hide')
					},5000)
				}else if(code == 2){
					$.ajax({
						type:'GET',
						url:'../cgi-bin/stopnode.cgi?para='+window.localStorage.getItem('sessionid'),
						success:function(data){
							if(data.ulord =='stop'){
								$('#confirm').modal('hide')
								myModal(0,'正在关闭主节点，这需要几分钟，请根据主节点信号灯判断是否关闭！',5000)
								setLocalStatus('status',3)
								$('#rpcName,#rpcPwd').attr('readonly',true)
								
							}else {
								window.localStorage.removeItem('sessionid')
								window.location.href="/"
							}
						},
						error:function(err,text){
							myModal(2,'网络异常，请稍后再试！',2000);
						}

					})
				}
				
				
			}

			// 主节点全局状态
			mainNodeStatus = {
				status:0,  /* 0:未启动 1：启动中 2：运行 3：关闭中 */
				operation:0 /* 0:无动作 1：启动中 2：关闭中*/
			}
			timestamp = Date.now()
			//操作按钮UI界面
			function setUlordStatus(status){
				switch(status){
					case 0:
					$('.checked-switch').prop('checked',false);
					$('.text-switch').attr('data-yes','启动').attr('data-no','未启动')
					$('#rpcName,#rpcPwd').attr('readonly',false)
					break;
					case 1:
					$('.checked-switch').prop('checked',false);
					$('.text-switch').attr('data-yes','启动中').attr('data-no','启动中')
					$('#rpcName,#rpcPwd').attr('readonly',true)
					break;
					case 2:
					$('.checked-switch').prop('checked',true);
					$('.text-switch').attr('data-yes','启动').attr('data-no','启动')
					$('#rpcName,#rpcPwd').attr('readonly',true)
					break;
					case 3:
					$('.checked-switch').prop('checked',false);
					$('.text-switch').attr('data-yes','关闭中').attr('data-no','关闭中')
					$('#rpcName,#rpcPwd').attr('readonly',true)
					break;
					default:
					break;
				}
			}
			function restoreStatus(data){
				if(window.localStorage.getItem('mainNodeStatus')){
					mainNodeStatus = JSON.parse(window.localStorage.getItem('mainNodeStatus'))
				}else {
					if(data.ulord == 'start'){
						mainNodeStatus.status = 2
					}else {
						mainNodeStatus.status = 0
					}
					mainNodeStatus.operation = 0
					window.localStorage.setItem('mainNodeStatus',JSON.stringify(mainNodeStatus))
				}
			}
			// 操作localStorage中的状态
			function setLocalStatus(name,value){
				mainNodeStatus[name] = value
				var raw =  JSON.parse(window.localStorage.getItem('mainNodeStatus'))
				raw[name] = value
				window.localStorage.setItem('mainNodeStatus',JSON.stringify(raw))
			}

			// 循环获取状态
			function getStatus(){
				if((Date.now() - timestamp)>120000){
					myModal(2,'与主节点通信不稳定，请稍后再试！',2000)
				}
				$.get('../cgi-bin/status.cgi',{
					para: window.localStorage.getItem('sessionid')
				},function(data){
					if(data.session!=="failed"){
						restoreStatus(data)					
						// 获取主节点程序状态
						$('.title2 span').removeClass('gray green').addClass(data.masternode=='start'?'green':'gray').text(data.masternode=='start'?'运行':'未运行')
						
						
						switch(mainNodeStatus.status){
							case 0:
							case 2:
							break;
							case 1:
							if(data.ulord == 'start'){
								myModal(1,'主节点启动成功！',5000)
								setLocalStatus('status',2)
							}
							break;

							case 3:
							if(data.ulord == 'stop'){
								myModal(1,'主节点关闭成功！',5000)
								setLocalStatus('status',0)
							}else {
								$.ajax({
									type:'GET',
									url:'../cgi-bin/stopnode.cgi?para='+window.localStorage.getItem('sessionid'),
									success:function(data){

									},
									error:function(err,text){
										myModal(2,'网络异常，请稍后再试！',2000);
									}

								})
							}
							break;
						}
						setUlordStatus(mainNodeStatus.status)
						timestamp = Date.now()


					}else {
						window.localStorage.removeItem('sessionid')
						window.location.href="/"
					}
				})
			}
			setInterval(getStatus,5000)
			getStatus()


			$('.checked-switch').on('click',function(e){
				e.preventDefault()
				switch(mainNodeStatus.status){
					case 1:
					case 3:
					break;
					case 2:
					setLocalStatus('operation',2)
					$('#confirm .modal-body .red').text('你正在关闭主节点')
					$('#confirm').modal('show')
					break;
					case 0:
					setLocalStatus('operation',1)
					$('#confirm .modal-body .red').text('你正在打开主节点')
					$('#confirm').modal('show')
					break;
					default:
					break;
				}
			})
			// 确认模态框按钮
			$('#continue').on('click',function(e){
				mainNodeOperate(mainNodeStatus.operation)
			})
			$('#cancelOp').on('click',function(e){
				setLocalStatus('operation',0)
			})

			// 初始化获取主节点配置
			$.ajax({
				url:'../cgi-bin/readcfg.cgi',
				type:'GET',
				data:"para="+window.localStorage.getItem('sessionid'),
				success:function(data){
					if(data.session!=="failed"){
						$('#rpcName').val(data.rpcuser)	/* RPC账号*/
						$('#rpcPwd').val(data.rpcpassword) /* RPC密码*/
						$('#featureCode').val(data.masternodeprivkey) /* 主节点的特征码*/
						$('#addIp').val(data.addnode)	/* 额外的同步节点*/
						$('#certificate').val(data.certificate) /* 证书 */
						$('#version').val(data.certifiversion) /* 证书版本*/
						$('#txIndex').val(data.collateraloutputindex) /* 交易索引*/
						$('#txHash').val(data.collateraloutputtxid)  /* 交易哈希*/
						$('#ipAddress').val(data.externalip)  /* 公网IP*/
						$('#nodeSign').val(data.broadcastsign) /* 广播的主节点签名 */
						$('#publicKey').val(data.uctpubkey1) /*验证证书的公钥*/
						$('#timestamp').val(data.certifiperiod) /*证书到期日期*/
						$('#formatedDate').text(new Date($('#timestamp').val()*1000).toLocaleString())
						if($('#certificate').val()){
							$('#timestamp,#version').attr('disabled',false)
						}
					}else {
						window.localStorage.removeItem('sessionid')
						window.location.href="/"
					}
					
				},
				error: function(error,txt){
					myModal(2,'网络异常，请稍后再试！',2000);
				}
			})
			$('#submitConfig').on('click', function() {
				if(validateInput()){
					book();
				}
				
			})
			$(document).on('keypress',function(e){
				var keyCode = e.keyCode || e.which
				if(keyCode==13){
					$('#submitConfig').trigger('click')
				}
			})
			// 导航栏
			$('#switcher').on('click',function(){
				$('.switch-container').toggleClass('in')
			})

			// 登出
			$('#logout').on('click',function(){
				$.get('../cgi-bin/logout.cgi',{
					para: window.localStorage.getItem('sessionid')
				},function(data){
					if(data.msg == 'success'){
						window.localStorage.removeItem('sessionid')
						window.location.href = '/'
					}
				})
			})

			$('#timestamp').on('input change',function(e){
				$('#formatedDate').text(new Date(e.target.value*1000).toLocaleString())
			})


		})
